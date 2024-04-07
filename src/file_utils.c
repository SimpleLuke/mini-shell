/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:52:45 by llai              #+#    #+#             */
/*   Updated: 2024/04/07 17:12:15 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_heredoc(t_data *data)
{
	int	i;

	i = 0;
	if (data->io.in_size)
	{
		i = 0;
		while (i < data->io.in_size)
		{
			if (data->io.infile_list[i].type == CHAR_HEREDOC)
			{
				if (data->in_fd != -1)
					close(data->in_fd);
				create_heredoc(data, data->io.infile_list[i]);
				data->in_fd = open(".temp_heredoc", O_RDONLY, 0666);
				if (data->in_fd == -1)
				{
					print_err("here_doc", strerror(errno), EXIT_FAILURE);
				}
				data->heredoc = true;
				data->io.infile_list[i].type = CHAR_LESSER;
				ft_free((void **)&data->io.infile_list[i].name);
				data->io.infile_list[i].name = ft_strdup(".temp_heredoc");
				// fprintf(stderr, "%d %s\n", data->io.infile_list[i].idx, data->io.infile_list[i].name);
			}
			i++;
		}
		// dup2(data->in_fd, STDIN_FILENO);
		// close(data->in_fd);
	}
}

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
	stdin_dup = dup(data->std_in);
	is_open = 1;
	while (true)
	{
		if (is_open)
			ft_putstr_fd("> ", data->std_out);
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
