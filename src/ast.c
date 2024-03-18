/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:07:47 by llai              #+#    #+#             */
/*   Updated: 2024/03/18 13:17:38 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <assert.h>

void	ASTattachBinaryBranch(t_ASTNode *root, t_ASTNode *leftNode, t_ASTNode *rightNode)
{
	assert(root != NULL);
	root->left = leftNode;
	root->right = rightNode;
}

void	ASTnodeSetType(t_ASTNode *node, NodeType nodetype)
{
	assert(node != NULL);
	node->type = nodetype;
}

void	ASTnodeSetData(t_ASTNode *node, char *data)
{
	assert(node != NULL);
	if (data != NULL)
	{
		node->data = data;
		node->type = node->type | NODE_DATA;
	}
}

void	ASTnodeDelete(t_ASTNode *node)
{
	if (node == NULL)
		return ;
	if (node->type & NODE_DATA)
		free(node->data);
	ASTnodeDelete(node->left);
	ASTnodeDelete(node->right);
	free(node);
}
