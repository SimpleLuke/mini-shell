/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:19:48 by llai              #+#    #+#             */
/*   Updated: 2024/06/27 17:20:02 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

// Helper function prototypes
void handle_redirections(t_data *data);
void handle_infile_redirection(t_data *data);
void handle_outfile_redirection(t_data *data);
void execute_child_process(t_ast *node, t_data *data);
void handle_builtin_and_exec(t_ast *node, t_data *data);

void execute_cmd(t_ast *node, t_data *data)
{
    pid_t pid;

    data->pids[data->child_idx] = fork();
    pid = data->pids[data->child_idx];
    if (pid == 0) // Child process
    {
        execute_child_process(node, data);
    }
    else if (pid < 0) // Fork failed
    {
        perror("fork");
        return;
    }
    data->child_idx++;
}

void execute_child_process(t_ast *node, t_data *data)
{
    if (data->cmd.rd_pipe != -1 && data->in_fd < 0)
        dup2(data->cmd.rd_pipe, STDIN_FILENO);
    if (data->cmd.wr_pipe != -1 && data->out_fd < 0)
        dup2(data->cmd.wr_pipe, STDOUT_FILENO);

    handle_redirections(data);
    close_fds(data);

    if (data->cmd.cmd == NULL)
        err_exit(EXIT_FAILURE, data);

    handle_builtin_and_exec(node, data);
}

void handle_redirections(t_data *data)
{
    if (data->io.in_size)
    {
        handle_infile_redirection(data);
    }

    if (data->io.out_size)
    {
        handle_outfile_redirection(data);
    }
}

void handle_infile_redirection(t_data *data)
{
    int i = 0;
    while (i < data->io.in_size)
    {
        if (data->io.infile_list[i].type == CHAR_LESSER && data->io.infile_list[i].idx == data->child_idx)
        {
            if (data->in_fd != -1)
                close(data->in_fd);
            data->in_fd = open(data->io.infile_list[i].name, O_RDONLY);
            if (data->in_fd == -1)
            {
                print_err(data->io.infile_list[i].name, strerror(errno), EXIT_FAILURE);
                exit(EXIT_FAILURE);
            }
        }
        i++;
    }
    dup2(data->in_fd, STDIN_FILENO);
}

void handle_outfile_redirection(t_data *data)
{
    int i = 0;
    while (i < data->io.out_size)
    {
        if (data->io.outfile_list[i].type == CHAR_GREATER && data->io.outfile_list[i].idx == data->child_idx)
        {
            if (data->out_fd > -1)
                close(data->out_fd);
            data->out_fd = open(data->io.outfile_list[i].name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        }
        else if (data->io.outfile_list[i].type == CHAR_APPEND && data->io.outfile_list[i].idx == data->child_idx)
        {
            if (data->out_fd > -1)
                close(data->out_fd);
            data->out_fd = open(data->io.outfile_list[i].name, O_WRONLY | O_CREAT | O_APPEND, 0666);
        }
        if (data->out_fd == -1)
        {
            print_err(data->io.outfile_list[i].name, strerror(errno), EXIT_FAILURE);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    dup2(data->out_fd, STDOUT_FILENO);
}

void handle_builtin_and_exec(t_ast *node, t_data *data)
{
    if (execute_builtins_redirect(node, data))
        exit(EXIT_SUCCESS);

    if (execve(data->cmd.cmd, data->cmd.cmd_args, data->env_list) == -1)
    {
        dup2(data->std_out, STDOUT_FILENO);
        err_exit(print_err(data->cmd.cmd_args[0], strerror(errno), EXIT_FAILURE), data);
    }
}
