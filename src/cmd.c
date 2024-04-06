/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:53:21 by llai              #+#    #+#             */
/*   Updated: 2024/04/06 15:16:15 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

char	*get_cmd(char *cmd, t_data *data);
char	**get_env_list(t_data *data);
void	format_list(char **env_list);

char	*get_cmd(char *cmd, t_data *data)
{
	char	**env_list;
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	env_list = get_env_list(data);
	i = -1;
	while (env_list[++i])
	{
		cmd_path = ft_strjoin(env_list[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		ft_free((void **)&cmd_path);
	}
	ft_free_strarr(&env_list);
	return (cmd_path);
}

char	**get_env_list(t_data *data)
{
	int		i;
	char	*path;
	char	**env_list;

	i = -1;
	path = NULL;
	while (data->env_list[++i])
	{
		if (!ft_strncmp("PATH=", data->env_list[i], 5))
		{
			path = data->env_list[i] + 5;
			break ;
		}
	}
	env_list = ft_split(path, ':');
	format_list(env_list);
	return (env_list);
}

void	format_list(char **env_list)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (env_list[++i])
	{
		tmp = env_list[i];
		env_list[i] = ft_strjoin(env_list[i], "/");
		ft_free((void **)&tmp);
	}
}

char	**get_cmd_args(t_ast *node)
{
	t_ast	*head;
	int		count;
	int		i;
	char	**result;

	(void)head;
	result = NULL;
	head = node;
	count = 0;
	i = 0;
	while (node != NULL)
	{
		count++;
		node = node->right;
	}
	result = malloc(sizeof(char *) * (count + 1));
	while (head != NULL)
	{
		result[i] = ft_strdup(head->data);
		head = head->right;
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	init_cmd(t_ast *node, t_data *data, int rd_pipe, int wr_pipe)
{
	data->cmd.cmd_args = get_cmd_args(node);
	data->cmd.cmd = get_cmd(node->data, data);
	if (!data->cmd.cmd)
		print_err(data->cmd.cmd_args[0], "command not found", EXIT_FAILURE);
	data->cmd.rd_pipe = rd_pipe;
	data->cmd.wr_pipe = wr_pipe;
	// print_strarr(data->cmd.cmd_args);
	return (0);
}

void	free_cmd(t_data *data)
{
	if (data->cmd.cmd)
		ft_free((void **)&data->cmd.cmd);
	ft_free_strarr(&data->cmd.cmd_args);
	data->cmd.rd_pipe = -1;
	data->cmd.wr_pipe = -1;
}

int	execute_builtins(t_ast *node, t_data *data)
{
	if (ft_strlen(node->data) == ft_strlen("echo") && ft_strncmp(node->data, "echo", 4) == 0)
	{
		if (arrlen(data->cmd.cmd_args) > 1 && data->cmd.cmd_args[1][0] == '-' && ft_strchr(data->cmd.cmd_args[1], 'n'))
			echo(true, data->cmd.cmd_args[arrlen(data->cmd.cmd_args) - 1]);
		else if (arrlen(data->cmd.cmd_args) > 1)
			echo(false, data->cmd.cmd_args[arrlen(data->cmd.cmd_args) - 1]);
		else
			echo(false, "");
		return (1);
	}
	return (0);
}

void	execute_cmd(t_ast *node, t_data *data)
{
	pid_t	pid;
	int		stdoutfd;
	int		in_fd;
	int		out_fd;
	int		i;
	// check built-ins
	if (execute_builtins(node, data))
		return ;
	// built in tbc

	in_fd = -1;
	out_fd = -1;
	data->pids[data->child_idx] = fork();
	pid = data->pids[data->child_idx];
	if (pid == 0)
	{
		stdoutfd = dup(STDOUT_FILENO);

		if (data->cmd.rd_pipe != -1 && in_fd == -1)
		{
			dup2(data->cmd.rd_pipe, STDIN_FILENO);
			// close(data->cmd.rd_pipe);

		}
		if (data->cmd.wr_pipe != -1 && out_fd == -1)
		{
			dup2(data->cmd.wr_pipe, STDOUT_FILENO);
			// close(data->cmd.wr_pipe);
		}

		if (data->io.in_size)
		{
			i = 0;
			while (i < data->io.in_size)
			{
				if (data->io.infile_list[i].type == CHAR_LESSER)
				{
					if (in_fd != -1)
						close(in_fd);
					in_fd = open(data->io.infile_list[i].name, O_RDONLY);
					if (in_fd == -1)
					{
						print_err(data->io.infile_list[i].name, strerror(errno), EXIT_FAILURE);
						exit(EXIT_FAILURE);
					}
				}
				i++;
			}
			dup2(in_fd, STDIN_FILENO);
			// close(in_fd);
		}

		if (data->io.out_size)
		{
			i = 0;
			while (i < data->io.out_size)
			{
				if (out_fd != -1)
					close(out_fd);
				if (data->io.outfile_list[i].type == CHAR_GREATER && data->io.outfile_list[i].idx == data->child_idx)
					out_fd = open(data->io.outfile_list[i].name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				else if (data->io.outfile_list[i].type == CHAR_APPEND)
					out_fd = open(data->io.outfile_list[i].name, O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (out_fd == -1)
				{
					print_err(data->io.outfile_list[i].name, strerror(errno), EXIT_FAILURE);
					exit(EXIT_FAILURE);
				}
				// printf("OUTFILE: %s i:%d idx:%d\n", data->io.outfile_list[i].name, i, data->io.outfile_list[i].idx);
				i++;
			}
			dup2(out_fd, STDOUT_FILENO);
			// close(out_fd);
		}

		// if (data->cmd.rd_pipe != -1 && in_fd == -1)
		// {
		// 	dup2(data->cmd.rd_pipe, STDIN_FILENO);
		// 	// close(data->cmd.rd_pipe);
		//
		// }
		// if (data->cmd.wr_pipe != -1 && out_fd == -1)
		// {
		// 	dup2(data->cmd.wr_pipe, STDOUT_FILENO);
		// 	// close(data->cmd.wr_pipe);
		// }

		if (data->cmd.cmd == NULL)
			err_exit(EXIT_FAILURE, data);
		if (execve(data->cmd.cmd, data->cmd.cmd_args, data->env_list) == -1)
		{
			dup2(stdoutfd, STDOUT_FILENO);
			err_exit(print_err(data->cmd.cmd_args[0], strerror(errno), EXIT_FAILURE), data);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		return ;
	}
	data->child_idx++;
	// while (waitpid(pid, NULL, 0) <= 0);
	return ;
}
