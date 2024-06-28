/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:08:51 by llai              #+#    #+#             */
/*   Updated: 2024/06/28 19:59:53 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

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

	(void)argc;
	(void)argv;
	data.env_list = copy_string_list(envp);
	init_data(&data);
	while (1)
	{
		if (take_input(&data))
			continue ;
		tokenize(&data);
		if (parse(&data) != 0)
			continue;
		execute_tree(&data);
		ast_node_delete(data.ast);
		data.ast = NULL;
		ft_lstclear(&(data.tk_list), free);
	}
	return (0);
}
