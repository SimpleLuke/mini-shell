/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:07:47 by llai              #+#    #+#             */
/*   Updated: 2024/03/24 16:48:31 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <assert.h>

void	ast_attach_binary_branch(t_ast *root, t_ast *leftNode, t_ast *rightNode)
{
	assert(root != NULL);
	root->left = leftNode;
	root->right = rightNode;
}

void	ast_node_set_type(t_ast *node, t_NodeType nodetype)
{
	assert(node != NULL);
	node->type = nodetype;
}

void	ast_node_set_data(t_ast *node, char *data)
{
	assert(node != NULL);
	if (data != NULL)
	{
		node->data = data;
		node->type = node->type | NODE_DATA;
	}
}

void	ast_node_delete(t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->type & NODE_DATA)
		free(node->data);
	ast_node_delete(node->left);
	ast_node_delete(node->right);
	free(node);
}
