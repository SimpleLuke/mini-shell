/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:39:10 by llai              #+#    #+#             */
/*   Updated: 2024/06/28 20:05:49 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int		print_err(char *msg1, char *msg2, int errstate);
void	err_exit(int errstate, t_data *data);

int	print_err(char *msg1, char *msg2, int errstate)
{
	ft_putstr_fd(msg1, 2);
	if (msg2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg2, 2);
	}
	ft_putstr_fd("\n", 2);
	return (errstate);
}

void	err_exit(int errstate, t_data *data)
{
	(void)data;
	exit(errstate);
}
