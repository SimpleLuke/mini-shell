/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:34:15 by llai              #+#    #+#             */
/*   Updated: 2024/04/06 18:26:51 by llai             ###   ########.fr       */
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

void	execute_job(t_ast *node, t_data *data)
{
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

	while (--data->child_idx >= 0)
	{
		wpid = waitpid(data->pids[data->child_idx], &status, 0);
		if (wpid == data->pids[data->cmd_count - 1])
			if ((data->child_idx == (data->cmd_count - 1)) && WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
	}
}

void	execute_tree(t_data *data)
{
	init_pids(data);
	data->child_idx = 0;
	execute_job(data->ast, data);
	run_parent(data);
}
