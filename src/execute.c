/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:34:15 by llai              #+#    #+#             */
/*   Updated: 2024/06/27 17:23:07 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

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
	int	wr_pipe;
	int	rd_pipe;
	t_ast	*next_node;

	pipe(data->pipe_fd);
	wr_pipe = data->pipe_fd[1];
	rd_pipe = data->pipe_fd[0];
	execute_cmdpath(node->left, data, 0, wr_pipe);
	next_node = node->right;
	while (next_node != NULL && NODETYPE(next_node->type) == NODE_PIPE)
	{
		close(wr_pipe);
		pipe(data->pipe_fd);
		wr_pipe = data->pipe_fd[1];
		execute_cmdpath(next_node->left, data, rd_pipe, wr_pipe);
		close(rd_pipe);
		rd_pipe = data->pipe_fd[0];
		next_node = next_node->right;
	}
	rd_pipe = data->pipe_fd[0];
	close(wr_pipe);
	execute_cmdpath(next_node, data, rd_pipe, 1);
	close(rd_pipe);
}

void	execute_job(t_ast *node, t_data *data)
{
	if (node == NULL)
		return ;
	if (NODETYPE(node->type) == NODE_PIPE)
	{
		data->pipe = true;
		execute_pipe(node, data);
	}
	else if (NODETYPE(node->type) == NODE_CMDPATH)
	{
		if (isbuiltins_in_parent(node))
		{
			execute_builtins_in_parent(node, data);
			return ;
		}
		execute_cmdpath(node, data, -1, -1);
	}
}

void	count_cmds(t_ast *root, t_data *data)
{
	if (root == NULL)
		return ;
	if (NODETYPE(root->type) == NODE_CMDPATH)
		data->cmd_count++;
	count_cmds(root->left, data);
	count_cmds(root->right, data);
}

void	init_pids(t_data *data)
{
	count_cmds(data->ast, data);
	data->pids = malloc(sizeof(int) * data->cmd_count);
}

void	run_parent(t_data *data)
{
	int	wpid;
	int	status;

	close_fds(data);
	while (--data->child_idx >= 0)
	{
		wpid = waitpid(data->pids[data->child_idx], &status, 0);
		if (wpid == data->pids[data->child_idx])
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
	}
	if (data->heredoc)
		unlink(".temp_heredoc");
}

void	execute_tree(t_data *data)
{
	init_pids(data);
	data->child_idx = 0;
	process_heredoc(data);
	if (!data->heredoc_code)
		execute_job(data->ast, data);
	run_parent(data);
}
