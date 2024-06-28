/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:53:21 by llai              #+#    #+#             */
/*   Updated: 2024/04/08 18:02:53 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdbool.h>
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
	while (env_list && env_list[++i])
	{
		cmd_path = ft_strjoin(env_list[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		ft_free((void **)&cmd_path);
	}
	if (env_list)
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
	env_list = NULL;
	while (data->env_list[++i])
	{
		if (!ft_strncmp("PATH=", data->env_list[i], 5))
		{
			path = data->env_list[i] + 5;
			break ;
		}
	}
	if (path)
	{
		env_list = ft_split(path, ':');
		format_list(env_list);
	}
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

bool	isbuiltins(t_ast *node)
{
	int	len;

	len = ft_strlen(node->data);
	
	if ((len == 4 && !ft_strncmp(node->data, "echo", 4)) 
		|| (len == 3 && !ft_strncmp(node->data, "pwd", 3))
		|| (len == 2 && !ft_strncmp(node->data, "cd", 2))
		|| (len == 3 && !ft_strncmp(node->data, "env", 3))
		|| (len == 5 && !ft_strncmp(node->data, "unset", 5))
		|| (len == 6 && !ft_strncmp(node->data, "export", 6))
		|| (len == 4 && !ft_strncmp(node->data, "exit", 4)))
	{
		return (true);
	}
	return (false);
}

bool	isbuiltins_in_parent(t_ast *node)
{
	int	len;

	len = ft_strlen(node->data);
	if ((len == 2 && !ft_strncmp(node->data, "cd", 2))
		|| (len == 5 && !ft_strncmp(node->data, "unset", 5))
		|| (len == 6 && !ft_strncmp(node->data, "export", 6))
		|| (len == 4 && !ft_strncmp(node->data, "exit", 4))
	)
		return (true);
	return (false);
}

int	init_cmd(t_ast *node, t_data *data, int rd_pipe, int wr_pipe)
{
	data->cmd.cmd_args = get_cmd_args(node);
	if (!isbuiltins(node))
		data->cmd.cmd = get_cmd(node->data, data);
	else
		data->cmd.cmd = ft_strdup(node->data);
	if (!data->cmd.cmd)
		print_err(data->cmd.cmd_args[0], "command not found", EXIT_FAILURE);
	data->cmd.rd_pipe = rd_pipe;
	data->cmd.wr_pipe = wr_pipe;
	data->in_fd = -2;
	data->out_fd = -2;
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

// Helper function for string comparison
bool str_eq(const char *str1, const char *str2) {
    return ft_strlen(str1) == ft_strlen(str2) && ft_strncmp(str1, str2, ft_strlen(str2)) == 0;
}

void handle_echo(t_data *data) {
    if (arrlen(data->cmd.cmd_args) > 2 && data->cmd.cmd_args[1][0] == '-' && ft_strchr(data->cmd.cmd_args[1], 'n')) {
        echo(true, data->cmd.cmd_args[arrlen(data->cmd.cmd_args) - 1]);
    } else if (arrlen(data->cmd.cmd_args) > 1 && data->cmd.cmd_args[1][0] == '-' && ft_strchr(data->cmd.cmd_args[1], 'n')) {
        echo(true, NULL);
    } else if (arrlen(data->cmd.cmd_args) > 1) {
        echo(false, data->cmd.cmd_args[arrlen(data->cmd.cmd_args) - 1]);
    } else {
        echo(false, "");
    }
}

void handle_cd(t_ast *node) {
    if (node->right != NULL) {
        cd(node->right->data);
    }
}

void handle_export(t_ast *node, t_data *data) {
    if (node->right != NULL) {
        // fprintf(stderr, "%s\n", node->right->data);
        export_var(node->right->data, data);
    }
}

void handle_unset(t_ast *node, t_data *data) {
    if (node->right != NULL) {
        // fprintf(stderr, "%s\n", node->right->data);
        unset_env(node->right->data, data);
    }
}

int execute_builtins_redirect(t_ast *node, t_data *data)
{
    if (str_eq(node->data, "echo"))
    {
        handle_echo(data);
        return (1);
    }
    if (str_eq(node->data, "pwd"))
    {
        pwd();
		return (1);
    }
    if (str_eq(node->data, "cd"))
    {
        handle_cd(node);
		return (1);
    }
    if (str_eq(node->data, "env"))
    {
        env(data->env_list);
		return (1);
    }
    if (str_eq(node->data, "export"))
    {
        handle_export(node, data);
		return (1);
    }
    if (str_eq(node->data, "exit"))
        // Handle exit if any additional logic is required
		return (1);
    if (str_eq(node->data, "unset"))
    {
        handle_unset(node, data);
		return (1);
    }
	return (0);
}

int execute_builtins_in_parent(t_ast *node, t_data *data)
{
    (void)data;
    (void)node;

    if (str_eq(node->data, "cd"))
    {
        handle_cd(node);
        return (1);
    }
    if (str_eq(node->data, "export"))
    {
        handle_export(node, data);
        return (1);
    }
    if (str_eq(node->data, "exit"))
    {
        exit_shell();
        return (1);
    }
    if (str_eq(node->data, "unset"))
    {
        handle_unset(node, data);
        return (1);
    }
    return (0);
}
