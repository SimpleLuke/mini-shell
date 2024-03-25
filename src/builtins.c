/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:08:01 by llai              #+#    #+#             */
/*   Updated: 2024/03/25 17:40:30 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void	echo(bool newline, char *str)
{
	printf("%s", str);
	if (newline)
		printf("\n");
}

int	set_cd_arg(char **arg, char *path, char lastdir[PATH_MAX])
{
	if (!ft_strncmp(*arg, "-", ft_strlen(*arg)))
	{
		if (*lastdir == '\0')
			return (pwd(), 1);
		*arg = lastdir;
	}
	else
	{
		if (**arg == '~')
		{
			if ((*arg)[1] == '/' || (*arg)[1] == '\0')
			{
				path = ft_strjoin(getenv("HOME"), *arg + 1);
				*arg = path;
			}
			else
			{
				printf("syntax not supported: %s\n", *arg);
				return (1);
			}
		}
	}
	return (0);
}

int	cd(char *arg)
{
	char		curdir[PATH_MAX];
	char		*path;
	static char	lastdir[PATH_MAX];

	path = NULL;
	getcwd(curdir, sizeof(curdir));
	if (arg == NULL)
		arg = getenv("HOME");
	if (set_cd_arg(&arg, path, lastdir))
		return (1);
	if (chdir(arg))
	{
		printf("chdir: %s: %s\n", strerror(errno), path);
		return (1);
	}
	ft_strlcpy(lastdir, curdir, ft_strlen(curdir) + 1);
	return (0);
}
