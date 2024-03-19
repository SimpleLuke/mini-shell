/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:07:47 by llai              #+#    #+#             */
/*   Updated: 2024/03/19 20:54:19 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <assert.h>

void	astAttachBinaryBranch(t_ast *root, t_ast *leftNode, t_ast *rightNode)
{
	assert(root != NULL);
	root->left = leftNode;
	root->right = rightNode;
}

void	astNodeSetType(t_ast *node, NodeType nodetype)
{
	assert(node != NULL);
	node->type = nodetype;
}

void	astNodeSetData(t_ast *node, char *data)
{
	assert(node != NULL);
	if (data != NULL)
	{
		node->data = data;
		node->type = node->type | NODE_DATA;
	}
}

void	astNodeDelete(t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->type & NODE_DATA)
		free(node->data);
	astNodeDelete(node->left);
	astNodeDelete(node->right);
	free(node);
}
