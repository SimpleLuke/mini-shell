/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:08:50 by llai              #+#    #+#             */
/*   Updated: 2024/03/13 16:30:22 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	tokenize(char *cmd_line, t_list **tk_list)
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
		if (ft_isalpha(*cmd_line) || *cmd_line == '-')
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(&(*cmd_line))));
		}
		cmd_line++;
		if (*cmd_line == ' ' || *cmd_line == '\0')
		{
			tmp_to_tokens(tk_list, tmp);
			ft_lstclear(&tmp, free);
		}
	}
}
