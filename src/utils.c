/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:05:41 by llai              #+#    #+#             */
/*   Updated: 2024/06/28 19:59:22 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_strarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

void	print_node(t_list *tk_list)
{
	t_token	*data;

	while (tk_list != NULL)
	{
		data = (t_token *)tk_list->content;
		printf("type: %d\n", data->type);
		printf("data: %s\n", data->data);
		tk_list = tk_list->next;
	}
}

void	print_tree_util(t_ast *root, int depth)
{
	if (root == NULL)
		return ;
	// Print the current node
	printf("%*sType: %d, Data: %s\n", depth * 4, "", root->type, root->data);
	// Print the left subtree
	printf("%*s\\--Left:\n", depth * 4, "");
	print_tree_util(root->left, depth + 1);
	// Print the right subtree
	printf("%*s\\--Right:\n", depth * 4, "");
	print_tree_util(root->right, depth + 1);
}

void	print_tree(t_ast *root)
{
	if (root == NULL)
	{
		printf("Tree is empty\n");
		return ;
	}
	printf("Root:\n");
	print_tree_util(root, 1);
}
