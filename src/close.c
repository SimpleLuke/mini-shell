/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:41:01 by llai              #+#    #+#             */
/*   Updated: 2024/04/07 15:13:04 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		close_fds(t_data *data);
static void	close_pipes(t_data *data);

void	close_fds(t_data *data)
{
	if (data->in_fd > -1)
		close(data->in_fd);
	if (data->out_fd > -1)
		close(data->out_fd);
	close_pipes(data);
}

static void	close_pipes(t_data *data)
{
	if (data->pipe)
	{
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
	}
}
