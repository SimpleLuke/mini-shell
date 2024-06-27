/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:27:57 by llai              #+#    #+#             */
/*   Updated: 2024/06/27 17:37:55 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdbool.h>
#include <stdlib.h>

char	*dquote_data(char *data)
{
	char	*result;

	result = malloc((ft_strlen(data) + 3) * sizeof(char));
	result = ft_strdup("\"");
	result = ft_strjoin_gnl(result, data, ft_strlen(data));
	result = ft_strjoin_gnl(result, "\"", 1);
	return (result);
}

void	add_dquote(t_ast *ast)
{
	char	*tmp;

	if (ast == NULL)
		return ;
	if (ast->type == NODE_ARGUMENT && ast->data != NULL && !(ast->data[0] == '\'' && ast->data[ft_strlen(ast->data) - 1] == '\'')
		&& !(ast->data[0] == '\"' && ast->data[ft_strlen(ast->data) - 0] == '\"'))
	{
		tmp = dquote_data(ast->data);
		free(ast->data);
		ast->data = tmp;
	}
	add_dquote(ast->left);
	add_dquote(ast->right);
}

char	*convert_quote(char *data)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (data[0] == '\'' && data[ft_strlen(data) - 1] == '\'')
	{
		result = malloc((ft_strlen(data) - 1) * sizeof(char));
		while (data[i])
		{
			if (data[i] != '\'')
			{
				result[j] = data[i];
				j++;
			}
			i++;
		}
		result[j] = '\0';
		return (result);
	}
	return (NULL);
}

void	expand_quote(t_ast *ast)
{
	char	*tmp;

	if (ast == NULL)
		return ;
	if (ast->data != NULL && ast->data[0] == '\'' && ast->data[ft_strlen(ast->data) - 1] == '\'')
	{
		tmp = convert_quote(ast->data);
		free(ast->data);
		ast->data = tmp;
	}
	expand_quote(ast->left);
	expand_quote(ast->right);
}

char	*get_env_value(char *env_var)
{
	char	*result;
	char	**tmp;

	tmp = ft_split(env_var, '=');
	result = ft_strdup(tmp[1]);
	ft_free_strarr(&tmp);
	return (result);
}

char	*get_envvar(char *arg, t_data *data)
{
	int	i;
	int	is_exist;
	char	*result;

	i = 0;
	result = NULL;
	while (data->env_list[i] != NULL)
	{
		if (exist_var(arg, (data->env_list[i]), &is_exist))
		{
			result = get_env_value(data->env_list[i]);
		}
		i++;
	}
	return (result);
}

char	*convert_dquote(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*result;
	char	*tmp;
	char	*envvar;

	i = 0;
	j = 0;
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
	{
		result = malloc((ft_strlen(str) - 0) * sizeof(char));
		while (str[i])
		{
			if (str[i] != '\"')
			{
				result[j] = str[i];
				j++;
			}
			i++;
		}
		result[j] = '\0';
		tmp = ft_strchr(result, '$');
		result[(int)(tmp - result)] = '\0';
		envvar = get_envvar((tmp + 1), data);
		if (envvar)
			result = ft_strjoin_gnl(result, envvar, ft_strlen(envvar));
		return (result);
	}
	return (NULL);
}

void	expand_dquote(t_ast *ast, t_data *data)
{
	char	*tmp;

	if (ast == NULL)
		return ;
	if (ast->data != NULL && ast->data[0] == '\"' && ast->data[ft_strlen(ast->data) - 1] == '\"')
	{
		tmp = convert_dquote(ast->data, data);
		free(ast->data);
		ast->data = tmp;
	}
	expand_dquote(ast->left, data);
	expand_dquote(ast->right, data);
}

void	expand_token(t_ast *ast, t_data *data)
{
	char	*tmp;

	if (ast == NULL)
		return ;
	if (ast->data != NULL)
	{
		if (ft_strlen(ast->data) == 2 && !ft_strncmp(ast->data, "$?", 2))
			tmp = ft_itoa(data->exit_code);
		else
			tmp = convert_token(ast->data, data);
		free(ast->data);
		ast->data = tmp;
	}
	expand_token(ast->left, data);
	expand_token(ast->right, data);
}
