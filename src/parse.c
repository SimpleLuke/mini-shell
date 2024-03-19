/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:27:33 by llai              #+#    #+#             */
/*   Updated: 2024/03/19 21:16:40 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast	*simplecmd1(t_data *data);
t_ast	*tokenlist(t_data *data);
t_ast	*tokenlist1(t_data *data);
t_ast	*tokenlist2(t_data *data);

bool	term(t_data *data, int tokentype, char **buffer)
{
	t_token	*token;

	// (void)buffer;
	if (data->cur_token == NULL)
		return (false);
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
	data->cur_token = data->cur_token->next;
	return (false);
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

	// printf("1\n");
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
	return (NULL);
}

int	parse(t_data *data)
{
	t_token	*token;

	if (data->tk_list == NULL)
		return (-1);
	data->cur_token = data->tk_list;
	data->ast = simplecmd(data);
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
