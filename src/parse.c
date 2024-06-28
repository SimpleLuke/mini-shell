/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:27:33 by llai              #+#    #+#             */
/*   Updated: 2024/06/28 20:25:10 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// <job>			::=		<command> '|' <job>
	// 					|	<command>
	//
	// <command>		::=	
//						|	<simple command> '<' <filename> 
	// 					|	<simple command> '>' <filename>
	// 					|	<simple command> '>>' <filename>
	// 					|	<simple command> '<<' <filename>
//						|	'>' <filename> <simple command>
	// 					|	<simple command>
	//
	// <simple command>::=		<pathname> <token list>
	//
	// <token list>	::=		<token> <token list>
	// 					|	(EMPTY)
	//

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_ast	*parse_command_path(t_data *data);
t_ast	*parse_token_list(t_data *data);
t_ast	*parse_argument_list(t_data *data);
t_ast	*parse_emtpy_argument(t_data *data);
t_ast	*parse_pipe_sequence(t_data *data);
t_ast	*parse_simple_command(t_data *data);

bool	term_match(t_data *data, int tokentype, char **buffer)
{
	t_token	*token;

	if (data->cur_token == NULL)
		return (false);
	token = (t_token *)data->cur_token->content;
	if (token->type == tokentype)
	{
		if (buffer != NULL)
		{
			*buffer = malloc(ft_strlen(token->data) + 1);
			ft_strlcpy(*buffer, token->data, ft_strlen(token->data) + 1);
		}
		data->cur_token = data->cur_token->next;
		return (true);
	}
	data->cur_token = data->cur_token->next;
	return (false);
}

t_ast	*parse_job(t_data *data)
{
	t_ast	*node;
	t_list	*tmp;

	tmp = data->cur_token;
	data->cur_token = tmp;
	// <command> '|' <job>
	node = parse_pipe_sequence(data);
	if (node != NULL)
		return (node);
	data->cur_token = tmp;
	// <command>
	node = parse_simple_command(data);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast	*parse_pipe_sequence(t_data *data)
{
	t_ast	*cmd_node;
	t_ast	*job_node;
	t_ast	*result;

	cmd_node = parse_simple_command(data);
	if (cmd_node == NULL)
		return (NULL);
	if (!term_match(data, CHAR_PIPE, NULL))
	{
		ast_node_delete(cmd_node);
		return (NULL);
	}
	job_node = parse_job(data);
	if (job_node == NULL)
	{
		ast_node_delete(job_node);
		return (NULL);
	}
	result = malloc(sizeof(t_ast));
	ast_node_set_type(result, NODE_PIPE);
	ast_attach_binary_branch(result, cmd_node, job_node);
	return (result);
}

t_ast	*parse_simple_command(t_data *data)
{
	t_ast	*node;
	t_list	*tmp;

	tmp = data->cur_token;
	data->cur_token = tmp;
	// <simple command>
	node = parse_command_path(data);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast	*parse_command_path(t_data *data)
{
	t_ast	*token_list_node;
	t_ast	*result;
	char	*pathname;

	if (!term_match(data, TOKEN, &pathname))
		return (NULL);
	// <pathname> <token list>
	token_list_node = parse_token_list(data);
	result = malloc(sizeof(t_ast));
	ast_node_set_type(result, NODE_CMDPATH);
	ast_node_set_data(result, pathname);
	ast_attach_binary_branch(result, NULL, token_list_node);
	return (result);
}

t_ast	*parse_token_list(t_data *data)
{
	t_list	*tmp;
	t_ast	*node;

	tmp = data->cur_token;
	data->cur_token = tmp;
	// <token> <token list>
	node = parse_argument_list(data);
	if (node != NULL)
		return (node);
	data->cur_token = tmp;
	return (NULL);
}

t_ast	*parse_argument_list(t_data *data)
{
	t_ast	*token_list_node;
	t_ast	*result;
	char	*arg;

	if (!term_match(data, TOKEN, &arg))
		return (NULL);
	token_list_node = parse_token_list(data);
	result = malloc(sizeof(t_ast));
	ast_node_set_type(result, NODE_ARGUMENT);
	ast_node_set_data(result, arg);
	ast_attach_binary_branch(result, NULL, token_list_node);
	return (result);
}

int	count_type(int type, t_list *tk_list)
{
	t_token	*token;
	int		count;

	count = 0;
	if (tk_list == NULL)
		return (count);
	while (tk_list)
	{
		token = tk_list->content;
		if (token->type == type)
			count++;
		tk_list = tk_list->next;
	}
	return (count);
}

int	count_type_in_token(int type, char *data)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (data == NULL)
		return (count);
	while (data[i])
	{
		if (data[i] == type)
			count++;
		i++;
	}
	return (count);
}

void	init_io(t_data *data)
{
	data->io.out_size = count_type(CHAR_GREATER, data->tk_list)
		+ count_type(CHAR_APPEND, data->tk_list);
	data->io.outfile_list = malloc(sizeof(t_outfile) * data->io.out_size);
	data->io.in_size = count_type(CHAR_LESSER, data->tk_list)
		+ count_type(CHAR_HEREDOC, data->tk_list);
	data->io.infile_list = malloc(sizeof(t_outfile) * data->io.in_size);
}

void	store_infile(t_data *data)
{
	t_list	*tmp;
	t_token	*token;
	int		i;
	int		child_idx;

	i = 0;
	child_idx = 0;
	tmp = data->tk_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == CHAR_LESSER || token->type == CHAR_HEREDOC)
		{
			data->io.infile_list[i].idx = child_idx;
			data->io.infile_list[i].type = token->type;
			token = tmp->next->content;
			data->io.infile_list[i].name = token->data;
			i++;
		}
		if (token->type == CHAR_PIPE)
			child_idx++;
		tmp = tmp->next;
	}
}

void	store_outfile(t_data *data)
{
	t_list	*tmp;
	t_token	*token;
	int		i;
	int		child_idx;

	i = 0;
	child_idx = 0;
	tmp = data->tk_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == CHAR_GREATER || token->type == CHAR_APPEND)
		{
			data->io.outfile_list[i].idx = child_idx;
			data->io.outfile_list[i].type = token->type;
			token = tmp->next->content;
			data->io.outfile_list[i].name = token->data;
			i++;
		}
		if (token->type == CHAR_PIPE)
			child_idx++;
		tmp = tmp->next;
	}
}

void	copy_list(t_data *data, t_list **new, t_list **new_head)
{
	if (*new == NULL)
	{
		*new = data->tk_list;
		*new_head = *new;
	}
	else
	{
		(*new)->next = data->tk_list;
		*new = (*new)->next;
	}
}

t_list	*list_no_redirection(t_data *data)
{
	t_list	*new;
	t_list	*new_head;
	t_token	*token;

	new = NULL;
	new_head = new;
	while (data->tk_list)
	{
		token = data->tk_list->content;
		if (token->type == CHAR_GREATER || token->type == CHAR_APPEND
			|| token->type == CHAR_LESSER || token->type == CHAR_HEREDOC)
			data->tk_list = data->tk_list->next;
		else
			copy_list(data, &new, &new_head);
		data->tk_list = data->tk_list->next;
	}
	new->next = NULL;
	return (new_head);
}

t_list	*clear_redirection(t_data *data)
{
	t_list	*new_head;

	if (data->tk_list == NULL)
		return (NULL);
	new_head = list_no_redirection(data);
	return (new_head);
}

void	store_redirection(t_data *data)
{
	t_list	*new;

	init_io(data);
	store_infile(data);
	store_outfile(data);
	new = clear_redirection(data);
	ft_lstclear(&(data->tk_list), free);
	data->tk_list = new;
}

int	check_unclosed(t_list *tk_list)
{
	t_token	*token;
	char	last;

	if (tk_list == NULL)
		return (0);
	while (tk_list)
	{
		token = tk_list->content;
		last = token->data[ft_strlen(token->data) - 1];
		if (token->data[0] == '\"' && last != '\"')
			return (printf("Syntax Error : unclosed double quote\n"), -1);
		if (token->data[0] == '\'' && last != '\'')
			return (printf("Syntax Error : unclosed quote\n"), -1);
		if ((token->data[0] == '\'' && last == '\'')
			&& count_type_in_token(CHAR_QOUTE, token->data) % 2)
			return (printf("Syntax Error : unclosed quote\n"), -1);
		if ((token->data[0] == '\"' && last == '\"')
			&& count_type_in_token(CHAR_DQUOTE, token->data) % 2)
			return (printf("Syntax Error : unclosed quote\n"), -1);
		tk_list = tk_list->next;
	}
	return (0);
}

int	check_doulbe_operation(t_list *tk_list)
{
	t_token	*cur_token;
	t_token	*next_token;

	if (tk_list == NULL)
		return (0);
	while (tk_list->next)
	{
		cur_token = tk_list->content;
		next_token = tk_list->next->content;
		if (cur_token->type != TOKEN && cur_token->type == next_token->type)
		{
			printf("Syntax Error near: %s\n", next_token->data);
			return (-1);
		}
		tk_list = tk_list->next;
	}
	return (0);
}

int	parse(t_data *data)
{
	t_token	*token;

	if (data->tk_list == NULL)
		return (-1);
	if (check_doulbe_operation(data->tk_list))
		return (-1);
	if (check_unclosed(data->tk_list))
		return (-1);
	store_redirection(data);
	data->cur_token = data->tk_list;
	data->ast = parse_job(data);
	if (data->cur_token != NULL)
		token = data->cur_token->content;
	if (data->cur_token != NULL && token->type != 0)
	{
		printf("Syntax Error near: %s\n", token->data);
		return (-1);
	}
	expand_token(data->ast, data);
	return (0);
}
