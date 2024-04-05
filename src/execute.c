/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:34:15 by llai              #+#    #+#             */
/*   Updated: 2024/04/05 15:41:44 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_simple_cmd(t_ast *node, t_data *data, int rd_pipe, int wr_pipe)
{
	init_cmd(node, data, rd_pipe, wr_pipe);
	execute_cmd(node, data);
	free_cmd(data);
}

void	execute_cmdpath(t_ast *node, t_data *data, int rd_pipe, int wr_pipe)
{
	if (node == NULL)
		return ;
	if (NODETYPE(node->type) == NODE_CMDPATH)
	{
		execute_simple_cmd(node, data, rd_pipe, wr_pipe);
	}
}

void	execute_pipe(t_ast *node, t_data *data)
{
	int	pipe_fd[2];
	int	wr_pipe;
	int	rd_pipe;
	t_ast	*next_node;

	pipe(pipe_fd);
	wr_pipe = pipe_fd[1];
	rd_pipe = pipe_fd[0];
	execute_cmdpath(node->left, data, 0, wr_pipe);
	next_node = node->right;
	while (next_node != NULL && NODETYPE(next_node->type) == NODE_PIPE)
	{
		close(wr_pipe);
		pipe(pipe_fd);
		wr_pipe = pipe_fd[1];
		data->child_idx++;
		execute_cmdpath(next_node->left, data, rd_pipe, wr_pipe);
		close(rd_pipe);
		rd_pipe = pipe_fd[0];
		next_node = next_node->right;
	}
	rd_pipe = pipe_fd[0];
	close(wr_pipe);
	execute_cmdpath(next_node, data, rd_pipe, 1);
	close(rd_pipe);
}

void	execute_job(t_ast *node, t_data *data, bool async)
{
	(void)async;
	if (node == NULL)
		return ;
	if (NODETYPE(node->type) == NODE_PIPE)
	{
		execute_pipe(node, data);
	}
	else if (NODETYPE(node->type) == NODE_CMDPATH)
	{
		execute_cmdpath(node, data, -1, -1);
	}

}

void	execute_tree(t_data *data)
{
	execute_job(data->ast, data, false);
}
