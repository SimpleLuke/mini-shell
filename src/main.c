/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:08:51 by llai              #+#    #+#             */
/*   Updated: 2024/03/25 18:37:13 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	init_data(t_data *data)
{
	data->input_string = NULL;
	data->tk_list = NULL;
	data->ast = NULL;
	data->cur_token = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	**env_list;

	(void)argc;
	(void)argv;
	env_list = copy_string_list(envp);
	init_data(&data);
	ignore_control_key();
	while (1)
	{
		env(env_list);
		export_var("a", &env_list);
		env(env_list);
		pwd();
		cd("..");
		pwd();
		cd("pipex");
		pwd();
		if (take_input(&data))
			continue ;
		tokenize(&data);
		print_node(data.tk_list);
		parse(&data);
		print_tree(data.ast);
		ast_node_delete(data.ast);
		ft_lstclear(&(data.tk_list), free);
	}
	return (0);
}
