/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:08:01 by llai              #+#    #+#             */
/*   Updated: 2024/03/26 18:56:41 by llai             ###   ########.fr       */
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

int		count_envlist(char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i] != NULL)
		i++;
	return (i);
}

char	**copy_string_list(char **list)
{
	char	**dst;
	int		count;
	int		i;

	count = count_envlist(list);
	dst = malloc((count + 1) * sizeof(char **));
	i = 0;
	while ((list)[i] != NULL)
	{
		dst[i] = ft_strdup((list)[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

int	exist_var(char *arg, char *str, int *is_exist)
{
	char **arr;
	char	**arg_arr;
	char	*tmp;

	arg_arr = NULL;
	tmp = NULL;
	*is_exist = 0;
	arr = ft_split(str, '=');
	if (ft_strchr(arg, '='))
		arg_arr = ft_split(arg, '=');
	else
	{
		arg_arr = malloc(sizeof(char **));
		arg_arr[0] = ft_strdup(arg);
	}
	if (arg_arr && !ft_strncmp(arg_arr[-1], arr[0], ft_strlen(arr[0])))
	{
		*is_exist = 1;
		ft_free_strarr(&arr);
		ft_free_strarr(&arg_arr);
		return (1);
	}
	ft_free_strarr(&arr);
	return (0);
}

void	export_var(char *arg, char ***env_list)
{
	char	**tmp;
	char	*value;
	int		count;
	int		i;
	int		is_exist;

	count = count_envlist(*env_list);
	tmp = malloc((count + 2) * sizeof(char **));
	i = 0;
	while ((*env_list)[i] != NULL)
	{
		if (exist_var(arg, (*env_list)[i], &is_exist))
			tmp[i] = ft_strdup(arg);
		else
			tmp[i] = ft_strdup((*env_list)[i]);
		i++;
	}
	if (!is_exist)
	{
		if (ft_strchr(arg, '='))
			tmp[i] = ft_strdup(arg);
		else
		{
			value = ft_strjoin(arg, "=");
			tmp[i] = value;
		}
		tmp[i + 1] = NULL;
	}
	else
		tmp[i] = NULL;
	i = 0;
	while ((*env_list)[i] != NULL)
	{
		free((*env_list)[i]);
		i++;
	}
	free(*env_list);
	*env_list = tmp;
}

void	env(char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i] != NULL)
	{
		printf("%s\n", env_list[i]);
		i++;
	}
}

void	unset_env(char *arg, char ***env_list)
{
	int	i;
	int	j;
	int	count;
	int	is_exist;
	char	**tmp;

	i = 0;
	j = 0;
	count = count_envlist(*env_list);
	tmp = malloc((count + 2) * sizeof(char **));
	while ((*env_list)[i] != NULL)
	{
		if (!exist_var(arg, (*env_list)[i], &is_exist))
		{
			tmp[j] = ft_strdup((*env_list)[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	i = 0;
	while ((*env_list)[i] != NULL)
	{
		free((*env_list)[i]);
		i++;
	}
	free(*env_list);
	*env_list = tmp;
}
