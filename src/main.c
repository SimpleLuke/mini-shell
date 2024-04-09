/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:08:51 by llai              #+#    #+#             */
/*   Updated: 2024/04/09 10:47:36 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

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
	if (root == NULL) return ;
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
	data->child_idx = 0;
	data->cmd_count = 0;
	data->heredoc = false;
	data->pipe = false;
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	data->heredoc_code = 0;
	data->exit_status = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	// char	**env_list;

	(void)argc;
	(void)argv;
	data.env_list = copy_string_list(envp);
	init_data(&data);
	// ignore_control_key();
	while (1)
	{
		// env(data.env_list);
		// export_var("a", &data.env_list);
		// env(data.env_list);
		// export_var("a=97", &env_list);
		// env(env_list);
		// unset_env("a", &env_list);
		// env(env_list);
		// pwd();
		// cd("..");
		// pwd();
		// cd("pipex");
		// pwd();
		// exit_shell();
		if (take_input(&data))
			continue ;
		tokenize(&data);
		// print_node(data.tk_list);
		if (parse(&data) != 0)
			continue;
		// print_tree(data.ast);
		execute_tree(&data);
		// printf("%s\n", data.cmd.cmd);
		ast_node_delete(data.ast);
		data.ast = NULL;
		ft_lstclear(&(data.tk_list), free);
	}
	return (0);
}
