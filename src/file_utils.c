/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:52:45 by llai              #+#    #+#             */
/*   Updated: 2024/04/07 15:02:46 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_heredoc(t_data *data, t_infile infile)
{
	int		fd;
	int		stdin_dup;
	int		is_open;
	char	*line;

	(void)data;
	fd = open(".temp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		print_err("here_doc", strerror(errno), EXIT_FAILURE);
	stdin_dup = dup(STDIN_FILENO);
	is_open = 1;
	while (true)
	{
		if (is_open)
			ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(stdin_dup);
		if (line == NULL)
			break ;
		if (ft_strlen(line) == ft_strlen(infile.name) + 1
			&& !ft_strncmp(line, infile.name, ft_strlen(infile.name)))
			is_open = close(stdin_dup);
		else
			ft_putstr_fd(line, fd);
		ft_free((void **)&line);
	}
	close(fd);
}
