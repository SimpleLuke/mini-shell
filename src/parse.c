/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:27:33 by llai              #+#    #+#             */
/*   Updated: 2024/03/21 22:21:46 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
	//
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

t_ast	*simplecmd(t_data *data);
t_ast	*simplecmd1(t_data *data);
t_ast	*tokenlist(t_data *data);
t_ast	*tokenlist1(t_data *data);
t_ast	*tokenlist2(t_data *data);
t_ast	*cmd(t_data *data);
t_ast	*cmd1(t_data *data);
t_ast	*cmd2(t_data *data);
t_ast	*cmd3(t_data *data);
t_ast	*cmd4(t_data *data);
t_ast	*cmd5(t_data *data);
t_ast	*cmd6(t_data *data);
t_ast	*job1(t_data *data);
t_ast	*job2(t_data *data);

bool	term(t_data *data, int tokentype, char **buffer)
{
	t_token	*token;

	// (void)buffer;
	if (data->cur_token == NULL)
	{
		// printf("1\n");
		return (false);
	}
	token = (t_token *)data->cur_token->content;
	// printf("HERE: %s\n", token->data);
	// printf("HERE: %d\n", token->type);
	// printf("HERE: %d\n", tokentype);
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
	// printf("2\n");
	data->cur_token = data->cur_token->next;
	return (false);
}

t_ast	*job(t_data *data)
{
	t_ast	*node;
	t_list *tmp;

	printf("job\n");
	tmp = data->cur_token;

	data->cur_token = tmp;
	// <command> '|' <job>
	node = job1(data);
	if (node != NULL)
		return (node);
	data->cur_token = tmp;
	// <command>
	node = job2(data);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast	*job1(t_data *data)
{
	t_ast	*cmdNode;
	t_ast	*jobNode;
	t_ast	*result;

	cmdNode = cmd(data);
	if (cmdNode == NULL)
		return (NULL);
	if (!term(data, CHAR_PIPE, NULL))
	{
		astNodeDelete(cmdNode);
		return (NULL);
	}
	jobNode = job(data);
	if (jobNode == NULL)
	{
		astNodeDelete(jobNode);
		return (NULL);
	}
	result = malloc(sizeof(t_ast));
	astNodeSetType(result, NODE_PIPE);
	astAttachBinaryBranch(result, cmdNode, jobNode);
	return (result);
}

t_ast	*job2(t_data *data)
{
	return (cmd(data));
}

t_ast	*cmd(t_data *data)
{
	t_ast	*node;
	t_list *tmp;

	printf("cmd\n");
	tmp = data->cur_token;

	// data->cur_token = tmp;
	// // <simple command> '<' <filename> 
	// node = cmd1(data);
	// if (node != NULL)
	// 	return (node);
	// data->cur_token = tmp;
	// // <simple command> '>' <filename> 
	// node = cmd2(data);
	// if (node != NULL)
	// 	return (node);
	// data->cur_token = tmp;
	// // <simple command> '>>' <filename> 
	// node = cmd3(data);
	// if (node != NULL)
	// 	return (node);
	// data->cur_token = tmp;
	// // <simple command> '<<' <filename> 
	// node = cmd4(data);
	// if (node != NULL)
	// 	return (node);
	// data->cur_token = tmp;
	// // '>' <filename> <simple command>
	// node = cmd6(data);
	// if (node != NULL)
	// 	return (node);
	data->cur_token = tmp;
	// <simple command>
	node = cmd5(data);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast	*cmd1(t_data *data)
{
	t_ast	*simplecmdNode;
	t_ast	*result;
	char	*filename;

	printf("cmd1\n");
	simplecmdNode = simplecmd(data);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(data, CHAR_LESSER, NULL))
	{
		astNodeDelete(simplecmdNode);
		return (NULL);
	}
	if (!term(data, TOKEN, &filename))
	{
		free(filename);
		astNodeDelete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(t_ast));
	astNodeSetType(result, NODE_REDIRECT_IN);
	astNodeSetData(result, filename);
	astAttachBinaryBranch(result, NULL, simplecmdNode);
	return (result);
}

t_ast	*cmd2(t_data *data)
{
	t_ast	*simplecmdNode;
	t_ast	*result;
	char	*filename;

	printf("cmd2\n");
	simplecmdNode = simplecmd(data);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(data, CHAR_GREATER, NULL))
	{
		// printf("1\n");
		astNodeDelete(simplecmdNode);
		return (NULL);
	}
	if (!term(data, TOKEN, &filename))
	{
		// printf("2\n");
		free(filename);
		astNodeDelete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(t_ast));
	astNodeSetType(result, NODE_REDIRECT_OUT);
	astNodeSetData(result, filename);
	astAttachBinaryBranch(result, NULL, simplecmdNode);
	// printTree(data->ast);
	return (result);
}

t_ast	*cmd3(t_data *data)
{
	t_ast	*simplecmdNode;
	t_ast	*result;
	char	*filename;

	printf("cmd2\n");
	simplecmdNode = simplecmd(data);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(data, CHAR_APPEND, NULL))
	{
		// printf("1\n");
		astNodeDelete(simplecmdNode);
		return (NULL);
	}
	if (!term(data, TOKEN, &filename))
	{
		// printf("2\n");
		free(filename);
		astNodeDelete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(t_ast));
	astNodeSetType(result, NODE_REDIRECT_APPREND);
	astNodeSetData(result, filename);
	astAttachBinaryBranch(result, NULL, simplecmdNode);
	// printTree(data->ast);
	return (result);
}

t_ast	*cmd4(t_data *data)
{
	t_ast	*simplecmdNode;
	t_ast	*result;
	char	*filename;

	printf("cmd2\n");
	simplecmdNode = simplecmd(data);
	if (simplecmdNode == NULL)
		return (NULL);
	if (!term(data, CHAR_HEREDOC, NULL))
	{
		// printf("1\n");
		astNodeDelete(simplecmdNode);
		return (NULL);
	}
	if (!term(data, TOKEN, &filename))
	{
		// printf("2\n");
		free(filename);
		astNodeDelete(simplecmdNode);
		return (NULL);
	}
	result = malloc(sizeof(t_ast));
	astNodeSetType(result, NODE_REDIRECT_HEREDOC);
	astNodeSetData(result, filename);
	astAttachBinaryBranch(result, NULL, simplecmdNode);
	// printTree(data->ast);
	return (result);
}

t_ast	*cmd6(t_data *data)
{
	t_ast	*simplecmdNode;
	t_ast	*result;
	char	*filename;

	printf("cmd6\n");
	if (!term(data, CHAR_GREATER, NULL))
	{
		// astNodeDelete(simplecmdNode);
		return (NULL);
	}
	if (!term(data, TOKEN, &filename))
	{
		free(filename);
		// astNodeDelete(simplecmdNode);
		return (NULL);
	}
	simplecmdNode = simplecmd(data);
	if (simplecmdNode == NULL)
		return (NULL);
	result = malloc(sizeof(t_ast));
	astNodeSetType(result, NODE_REDIRECT_OUT);
	astNodeSetData(result, filename);
	astAttachBinaryBranch(result, NULL, simplecmdNode);
	return (result);
}

t_ast	*cmd5(t_data *data)
{
	printf("cmd5\n");
	return (simplecmd(data));
}

t_ast	*simplecmd(t_data *data)
{
	// t_list *tmp;
	//
	// tmp = data->cur_token;
	return (simplecmd1(data));
}

t_ast	*simplecmd1(t_data *data)
{
	t_ast	*tokenListNode;
	t_ast	*result;
	char		*pathname;

	printf("simplecmd1\n");
	if (!term(data, TOKEN, &pathname))
		return (NULL);
	// <pathname> <token list>
	tokenListNode = tokenlist(data);
	result = malloc(sizeof(t_ast));
	astNodeSetType(result, NODE_CMDPATH);
	astNodeSetData(result, pathname);
	astAttachBinaryBranch(result, NULL, tokenListNode);
	return (result);
}

t_ast	*tokenlist(t_data *data)
{
	t_list	*tmp;
	t_ast	*node;

	tmp = data->cur_token;

	printf("tokenlist\n");
	data->cur_token = tmp;
	// <token> <token list>
	node = tokenlist1(data);
	if (node != NULL)
		return (node);
	data->cur_token = tmp;
	// (EMPTY)
	node = tokenlist2(data);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast	*tokenlist1(t_data *data)
{
	t_ast	*tokenListNode;
	t_ast	*result;
	char		*arg;

	printf("tokenlist1\n");
	if (!term(data, TOKEN, &arg))
		return (NULL);
	tokenListNode = tokenlist(data);
	result = malloc(sizeof(t_ast));
	astNodeSetType(result, NODE_ARGUMENT);
	astNodeSetData(result, arg);
	astAttachBinaryBranch(result, NULL, tokenListNode);
	return (result);
}

t_ast	*tokenlist2(t_data *data)
{
	(void)data;
	printf("tokenlist2\n");
	return (NULL);
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

void	init_io(t_data *data)
{
	data->io.out_size = count_type(CHAR_GREATER, data->tk_list) + count_type(CHAR_APPEND, data->tk_list);
	data->io.outfile_list = malloc(sizeof(t_outfile) * data->io.out_size);
	data->io.in_size = count_type(CHAR_LESSER, data->tk_list) + count_type(CHAR_HEREDOC, data->tk_list);
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

t_list	*clear_redirection(t_data *data)
{
	// t_list	*tmp;
	t_list	*new;
	t_list	*new_head;
	t_token	*token;
	int		i;

	i = 0;
	// tmp = data->tk_list;
	new = NULL;
	new_head = new;
	if (data->tk_list == NULL)
		return (NULL);
	while (data->tk_list)
	{
		token = data->tk_list->content;
		// printf("CONTENT: %s\n", token->data);
		if (token->type == CHAR_GREATER || token->type == CHAR_APPEND || token->type == CHAR_LESSER || token->type == CHAR_HEREDOC)
		{
			data->tk_list = data->tk_list->next;
			// printf("CON: %s\n", token->data);
		}
		else 
		{
			if (new == NULL)
			{
				new = data->tk_list;
				new_head = new;
				// token = new->content;
				// printf("IN: %s\n", token->data);
			}
			else
			{
				new->next = data->tk_list;
				new = new->next;
				// token = new->content;
				// printf("IN: %s\n", token->data);
			}
		}
		data->tk_list = data->tk_list->next;
	}
	new->next = NULL;
	// token = (new_head)->content;
	// printf("!!!: %s\n", token->data);
	// token = (new_head)->next->content;
	// printf("!!!: %s\n", token->data);
	// data->tk_list = *new_head;
	// ft_lstclear(&tmp, free);
	return (new_head);
	// printf("HERE!!!!\n");
	// print_node(data->tk_list);
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
	print_node(data->tk_list);
	// printf("child: %d type:%d name:%s\n",data->io.infile_list[0].idx, data->io.infile_list[0].type, data->io.infile_list[0].name);
	// printf("child: %d type:%d name:%s\n",data->io.infile_list[1].idx, data->io.infile_list[1].type, data->io.infile_list[1].name);
	// printf("child: %d type:%d name:%s\n",data->io.outfile_list[0].idx, data->io.outfile_list[0].type, data->io.outfile_list[0].name);
	// printf("child: %d type:%d name:%s\n",data->io.outfile_list[1].idx, data->io.outfile_list[1].type, data->io.outfile_list[1].name);
}

int	check_unclosed(t_list *tk_list)
{
	t_token	*token;
	int		i;

	i = 0;
	if (tk_list == NULL)
		return (0);
	while (tk_list)
	{
		token = tk_list->content;
		if (token->data[0] == '\"' && token->data[ft_strlen(token->data) - 1] != '\"')
		{
			printf("Syntax Error : unclosed double quote\n");
			return (-1);
		}
		if (token->data[0] == '\'' && token->data[ft_strlen(token->data) - 1] != '\'')
		{
			printf("Syntax Error : unclosed quote\n");
			return (-1);
		}
		tk_list = tk_list->next;
	}
	return (0);
}

int	check_doulbe_redirection(t_list *tk_list)
{
	t_token	*cur_token;
	t_token	*next_token;

	if (tk_list == NULL)
		return (0);
	while (tk_list)
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
	if (check_doulbe_redirection(data->tk_list))
		return (-1);
	if (check_unclosed(data->tk_list))
		return (-1);
	store_redirection(data);
	data->cur_token = data->tk_list;
	// data->ast = simplecmd(data);
	// data->ast = cmd(data);
	data->ast = job(data);
	// printf("2\n");
	if (data->cur_token != NULL)
		token = data->cur_token->content;
	if (data->cur_token != NULL && token->type != 0)
	{
		printf("Syntax Error near: %s\n", token->data);
		return (-1);
	}

	return (0);
}
