/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:27:33 by llai              #+#    #+#             */
/*   Updated: 2024/06/27 17:37:42 by llai             ###   ########.fr       */
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

t_ast	*parse_job(t_data *data);
t_ast	*parse_pipe_sequence(t_data *data);
t_ast	*parse_simple_command(t_data *data);
t_ast	*parse_command_path(t_data *data);
t_ast	*parse_token_list(t_data *data);
t_ast	*parse_argument_list(t_data *data);
t_ast	*parse_empty_argument(t_data *data);

bool	term_match(t_data *data, int tokentype, char **buffer)
{
	t_token	*token;

	if (data->cur_token == NULL)
		return false;
	token = (t_token *)data->cur_token->content;
	if (token->type == tokentype)
	{
		if (buffer != NULL)
		{
			*buffer = malloc(ft_strlen(token->data) + 1);
			ft_strlcpy(*buffer, token->data, ft_strlen(token->data) + 1);
		}
		data->cur_token = data->cur_token->next;
		return true;
	}
	data->cur_token = data->cur_token->next;
	return false;
}

t_ast	*parse_job(t_data *data)
{
	t_ast	*node;
	t_list	*tmp;

	tmp = data->cur_token;
	data->cur_token = tmp;
	node = parse_pipe_sequence(data);
	if (node != NULL)
		return node;
	data->cur_token = tmp;
	node = parse_simple_command(data);
	if (node != NULL)
		return node;
	return NULL;
}

t_ast	*parse_pipe_sequence(t_data *data)
{
	t_ast	*cmd_node;
	t_ast	*job_node;
	t_ast	*result;

	cmd_node = parse_command_path(data);
	if (cmd_node == NULL)
		return NULL;
	if (!term_match(data, CHAR_PIPE, NULL))
	{
		ast_node_delete(cmd_node);
		return NULL;
	}
	job_node = parse_job(data);
	if (job_node == NULL)
	{
		ast_node_delete(cmd_node);
		return NULL;
	}
	result = malloc(sizeof(t_ast));
	ast_node_set_type(result, NODE_PIPE);
	ast_attach_binary_branch(result, cmd_node, job_node);
	return result;
}

t_ast	*parse_simple_command(t_data *data)
{
	return parse_command_path(data);
}

t_ast	*parse_command_path(t_data *data)
{
	t_ast	*token_list_node;
	t_ast	*result;
	char	*pathname;

	if (!term_match(data, TOKEN, &pathname))
		return NULL;
	token_list_node = parse_token_list(data);
	result = malloc(sizeof(t_ast));
	ast_node_set_type(result, NODE_CMDPATH);
	ast_node_set_data(result, pathname);
	ast_attach_binary_branch(result, NULL, token_list_node);
	return result;
}

t_ast	*parse_token_list(t_data *data)
{
	t_list	*tmp;
	t_ast	*node;

	tmp = data->cur_token;
	data->cur_token = tmp;
	node = parse_argument_list(data);
	if (node != NULL)
		return node;
	data->cur_token = tmp;
	node = parse_empty_argument(data);
	if (node != NULL)
		return node;
	return NULL;
}

t_ast	*parse_argument_list(t_data *data)
{
	t_ast	*token_list_node;
	t_ast	*result;
	char	*arg;

	if (!term_match(data, TOKEN, &arg))
		return NULL;
	token_list_node = parse_token_list(data);
	result = malloc(sizeof(t_ast));
	ast_node_set_type(result, NODE_ARGUMENT);
	ast_node_set_data(result, arg);
	ast_attach_binary_branch(result, NULL, token_list_node);
	return result;
}

t_ast	*parse_empty_argument(t_data *data)
{
	(void)data;  // No tokens needed for an empty argument
	return NULL;
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
