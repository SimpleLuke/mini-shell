/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:27:33 by llai              #+#    #+#             */
/*   Updated: 2024/03/19 23:15:42 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast	*simplecmd(t_data *data);
t_ast	*simplecmd1(t_data *data);
t_ast	*tokenlist(t_data *data);
t_ast	*tokenlist1(t_data *data);
t_ast	*tokenlist2(t_data *data);
t_ast	*cmd(t_data *data);
t_ast	*cmd1(t_data *data);
t_ast	*cmd2(t_data *data);
t_ast	*cmd3(t_data *data);
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
	node = job1(data);
	if (node != NULL)
		return (node);
	data->cur_token = tmp;
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

	data->cur_token = tmp;
	node = cmd1(data);
	if (node != NULL)
		return (node);
	data->cur_token = tmp;
	node = cmd2(data);
	if (node != NULL)
		return (node);
	data->cur_token = tmp;
	node = cmd3(data);
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
	printf("cmd3\n");
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
	node = tokenlist1(data);
	if (node != NULL)
		return (node);
	data->cur_token = tmp;
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

int	parse(t_data *data)
{
	t_token	*token;

	if (data->tk_list == NULL)
		return (-1);
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
