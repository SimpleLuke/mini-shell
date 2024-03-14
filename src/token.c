/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:08:50 by llai              #+#    #+#             */
/*   Updated: 2024/03/14 17:35:00 by llai             ###   ########.fr       */
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

void	tmp_to_tokens(t_list **tk_list, t_list *tmp)
{
	int	size;
	int	i;
	char	*token;

	i = 0;
	if (tmp == NULL)
		return ;
	size = ft_lstsize(tmp);
	token = malloc((size + 1) * sizeof(char));
	while (i < size)
	{
		token[i] = *(char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	token[i] = '\0';
	ft_lstadd_back(tk_list, ft_lstnew(token));
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

void	tokenize(char *cmd_line, t_list **tk_list)
{
	int state;
	t_list	*tmp;
	int chtype;
	int	i;

	i = 0;
	tmp = NULL;
	if (*cmd_line == '\0')
		return ;
	state = STATE_GENERAL;
	while (1)
	{
		chtype = getchartype(cmd_line[i]);
		if (state == STATE_GENERAL)
		{
			if (chtype == CHAR_QOUTE)
			{
				state = STATE_IN_QUOTE;
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(cmd_line[i]))));
			}
			else if (chtype == CHAR_DQUOTE)
			{
				state = STATE_IN_DQUOTE;
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(cmd_line[i]))));
			}
			else if (chtype == CHAR_GENERAL)
			{
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(cmd_line[i]))));
			}
			else if (chtype == CHAR_GREATER || chtype == CHAR_LESSER || chtype == CHAR_PIPE)
			{
				if (tmp != NULL)
				{
					tmp_to_tokens(tk_list, tmp);
					ft_lstclear(&tmp, free);
				}
				ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(cmd_line[i]))));
				tmp_to_tokens(tk_list, tmp);
				ft_lstclear(&tmp, free);
			}
			else if (chtype == CHAR_WHITESPACE || chtype == CHAR_NULL)
			{
				tmp_to_tokens(tk_list, tmp);
				ft_lstclear(&tmp, free);
			}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(cmd_line[i]))));
			if (cmd_line[i] == CHAR_DQUOTE)
				state = STATE_GENERAL;
		}
		else if (state == STATE_IN_QUOTE)
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(cmd_line[i]))));
			if (cmd_line[i] == CHAR_QOUTE)
				state = STATE_GENERAL;
		}
		if (cmd_line[i] == '\0')
			break ;
		i++;
	}
}

void	tokenize2(char *cmd_line, t_list **tk_list)
{
	// char	*str;
	// char	*src;
	// t_list	*tk_node;
	t_list	*tmp;

	tmp = NULL;
	if (*cmd_line == '\0')
		return ;
	// src = cmd_line;
	// str = ft_strdup("");
	while (*cmd_line != '\0')
	{
		if (ft_isalnum(*cmd_line) || *cmd_line == '-' || *cmd_line == '_' || ft_isfilename(*cmd_line))
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(*cmd_line))));
		}
		else if (*cmd_line == '<')
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(*cmd_line))));
			tmp_to_tokens(tk_list, tmp);
			ft_lstclear(&tmp, free);
			cmd_line++;
			continue;
		}
		else if (*cmd_line == '>')
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(*cmd_line))));
			tmp_to_tokens(tk_list, tmp);
			ft_lstclear(&tmp, free);
			cmd_line++;
			continue;
		}
		cmd_line++;
		if (*cmd_line == ' ' || *cmd_line == '\0' || *cmd_line == '>' || *cmd_line == '<')
		{
			tmp_to_tokens(tk_list, tmp);
			ft_lstclear(&tmp, free);
		}
	}
}
