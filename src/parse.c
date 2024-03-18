/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:27:33 by llai              #+#    #+#             */
/*   Updated: 2024/03/18 13:50:47 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ASTNode	*simplecmd1(t_list **cur_token);
t_ASTNode	*tokenlist(t_list **cur_token);
t_ASTNode	*tokenlist1(t_list **cur_token);
t_ASTNode	*tokenlist2(t_list **cur_token);

t_ASTNode	*simplecmd(t_list **cur_token)
{
	t_list *tmp;

	tmp = *cur_token;
	return (simplecmd1(cur_token));
}

t_ASTNode	*simplecmd1(t_list **cur_token)
{
	t_ASTNode	*tokenListNode;
	t_ASTNode	*result;
	char		*pathname;

	tokenListNode = tokenlist(cur_token);
}

t_ASTNode	*tokenlist(t_list **cur_token)
{
	t_list	*tmp;
	t_ASTNode	*node;

	tmp = *cur_token;

	*cur_token = tmp;
	node = tokenlist1(cur_token);
	if (node != NULL)
		return (node);
	*cur_token = tmp;
	node = tokenlist2(cur_token);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ASTNode	*tokenlist1(t_list **cur_token)
{
	t_ASTNode	*tokenListNode;
	t_ASTNode	*result;
	char		*arg;
}

int	parse(t_list *token_list, t_ASTNode **syntax_tree)
{
	t_list *cur_token;

	cur_token = NULL;
	if (token_list == NULL)
		return (-1);
	cur_token = token_list;
	*syntax_tree = simplecmd(&cur_token);
}
