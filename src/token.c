/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:08:50 by llai              #+#    #+#             */
/*   Updated: 2024/03/20 17:28:32 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int getchartype(char c)
{
	if (c == '\'')
		return CHAR_QOUTE;
	else if (c == '\"')
		return CHAR_DQUOTE;
	else if (c == '|')
		return CHAR_PIPE;
	else if (c == ' ')
		return CHAR_WHITESPACE;
	else if (c== '\\')
		return CHAR_ESCAPESEQUENCE;
	else if (c == '\t')
		return CHAR_TAB;
	else if (c == '\n')
		return CHAR_NEWLINE;
	else if (c == '>')
		return CHAR_GREATER;
	else if (c == '<')
		return CHAR_LESSER;
	else if (c == '\0')
		return CHAR_NULL;
	else
		return CHAR_GENERAL;
}

void	tmp_to_tokens(t_data *data, t_list *tmp, int type)
{
	int	size;
	int	i;
	char	*tokenstr;
	t_token	*token;

	i = 0;
	if (tmp == NULL)
		return ;
	size = ft_lstsize(tmp);
	tokenstr = malloc((size + 1) * sizeof(char));
	while (i < size)
	{
		tokenstr[i] = *(char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	tokenstr[i] = '\0';
	token = (t_token *)malloc(sizeof(t_token));
	token->data = tokenstr;
	token->type = type;
	ft_lstadd_back(&data->tk_list, ft_lstnew(token));
}

int	ft_isfilename(char c)
{
	if (c == '#' || c == '%' || c == '+' || c == ',' || c == '-' || 
		c == '.' || c == '/' || c == ':' || c == '?' || c == '@' ||
		c == 92 || c == '^' || c == 94 || c == 96 || c == '{' ||
		c == '}' || c == '~')
		return (1);
	return (0);
}

// void	tokenize(char *data->inputString, t_list **data->tk_list)
void	tokenize(t_data *data)
{
	int state;
	t_list	*tmp;
	int chtype;
	int	i;

	i = 0;
	tmp = NULL;
	if (*data->inputString == '\0')
		return ;
	state = STATE_GENERAL;
	while (1)
	{
		chtype = getchartype(data->inputString[i]);
		if (state == STATE_GENERAL)
		{
			if (chtype == CHAR_QOUTE)
			{
				state = STATE_IN_QUOTE;
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[i]))));
			}
			else if (chtype == CHAR_DQUOTE)
			{
				state = STATE_IN_DQUOTE;
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[i]))));
			}
			else if (chtype == CHAR_ESCAPESEQUENCE)
			{
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[++i]))));
			}
			else if (chtype == CHAR_GENERAL)
			{
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[i]))));
			}
			else if (chtype == CHAR_GREATER || chtype == CHAR_LESSER || chtype == CHAR_PIPE)
			{
				if (tmp != NULL)
				{
					tmp_to_tokens(data, tmp, TOKEN);
					ft_lstclear(&tmp, free);
				}
				if (chtype == CHAR_GREATER && data->inputString[i + 1] == CHAR_GREATER)
				{
					ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[i]))));
					ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[++i]))));
					tmp_to_tokens(data, tmp, CHAR_APPEND);
					ft_lstclear(&tmp, free);
					i++;
					continue;
				}
				if (chtype == CHAR_LESSER && data->inputString[i + 1] == CHAR_LESSER)
				{
					ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[i]))));
					ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[++i]))));
					tmp_to_tokens(data, tmp, CHAR_HEREDOC);
					ft_lstclear(&tmp, free);
					i++;
					continue;

				}
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[i]))));
				tmp_to_tokens(data, tmp, chtype);
				ft_lstclear(&tmp, free);
			}
			else if (chtype == CHAR_WHITESPACE || chtype == CHAR_TAB || chtype == CHAR_NULL)
			{
				tmp_to_tokens(data, tmp, TOKEN);
				ft_lstclear(&tmp, free);
			}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[i]))));
			if (data->inputString[i] == CHAR_DQUOTE)
				state = STATE_GENERAL;
			else if (data->inputString[i] == CHAR_NULL)
			{
				tmp_to_tokens(data, tmp, TOKEN);
				ft_lstclear(&tmp, free);
			}
		}
		else if (state == STATE_IN_QUOTE)
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(data->inputString[i]))));
			if (data->inputString[i] == CHAR_QOUTE)
				state = STATE_GENERAL;
			else if (data->inputString[i] == CHAR_NULL)
			{
				tmp_to_tokens(data, tmp, TOKEN);
				ft_lstclear(&tmp, free);
			}
		}
		if (data->inputString[i] == CHAR_NULL)
			break ;
		i++;
	}
}
