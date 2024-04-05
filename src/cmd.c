/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:53:21 by llai              #+#    #+#             */
/*   Updated: 2024/04/05 13:43:32 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	init_cmd(t_ast *node, t_data *data)
{
	data->cmd.cmd = get_cmd(node->data, data);
	data->cmd.cmd_args = get_cmd_args(node);
	// print_strarr(data->cmd.cmd_args);
	return (0);
}

void	execute_cmd(t_ast *node, t_data *data)
{
	pid_t	pid;
	// check built-ins
	if (ft_strlen(node->data) == ft_strlen("echo") && ft_strncmp(node->data, "echo", 4) == 0)
	{
		if (arrlen(data->cmd.cmd_args) > 1 && data->cmd.cmd_args[1][0] == '-' && ft_strchr(data->cmd.cmd_args[1], 'n'))
			echo(true, data->cmd.cmd_args[arrlen(data->cmd.cmd_args) - 1]);
		else if (arrlen(data->cmd.cmd_args) > 1)
			echo(false, data->cmd.cmd_args[arrlen(data->cmd.cmd_args) - 1]);
		else
			echo(false, "");
		return ;
	}
	// built in tbc

	pid = fork();
	if (pid == 0)
	{
		if (execve(data->cmd.cmd, data->cmd.cmd_args, data->env_list) == -1)
		{
			err_exit(print_err(data->cmd.cmd_args[0], strerror(errno), EXIT_FAILURE), data);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		return ;
	}
	while (waitpid(pid, NULL, 0) <= 0);
	return ;
}
