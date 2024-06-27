/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:35:45 by llai              #+#    #+#             */
/*   Updated: 2024/06/27 17:35:51 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_type(int type, t_list *tk_list)
{
	t_token	*token;
	int		count;

	count = 0;
	if (tk_list == NULL)
		return (count);
	while (tk_list)
	{
		token = tk_list->content;
		if (token->type == type)
			count++;
		tk_list = tk_list->next;
	}
	return (count);
}

int	count_type_in_token(int type, char *data)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (data == NULL)
		return (count);
	while (data[i])
	{
		if (data[i] == type)
			count++;
		i++;
	}
	return (count);
}

void	init_io(t_data *data)
{
	data->io.out_size = count_type(CHAR_GREATER, data->tk_list)
		+ count_type(CHAR_APPEND, data->tk_list);
	data->io.outfile_list = malloc(sizeof(t_outfile) * data->io.out_size);
	data->io.in_size = count_type(CHAR_LESSER, data->tk_list)
		+ count_type(CHAR_HEREDOC, data->tk_list);
	data->io.infile_list = malloc(sizeof(t_outfile) * data->io.in_size);
}

void	store_infile(t_data *data)
{
	t_list	*tmp;
	t_token	*token;
	int		i;
	int		child_idx;

	i = 0;
	child_idx = 0;
	tmp = data->tk_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == CHAR_LESSER || token->type == CHAR_HEREDOC)
		{
			data->io.infile_list[i].idx = child_idx;
			data->io.infile_list[i].type = token->type;
			token = tmp->next->content;
			data->io.infile_list[i].name = token->data;
			i++;
		}
		if (token->type == CHAR_PIPE)
			child_idx++;
		tmp = tmp->next;
	}
}

void	store_outfile(t_data *data)
{
	t_list	*tmp;
	t_token	*token;
	int		i;
	int		child_idx;

	i = 0;
	child_idx = 0;
	tmp = data->tk_list;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == CHAR_GREATER || token->type == CHAR_APPEND)
		{
			data->io.outfile_list[i].idx = child_idx;
			data->io.outfile_list[i].type = token->type;
			token = tmp->next->content;
			data->io.outfile_list[i].name = token->data;
			i++;
		}
		if (token->type == CHAR_PIPE)
			child_idx++;
		tmp = tmp->next;
	}
}

void	copy_list(t_data *data, t_list **new, t_list **new_head)
{
	if (*new == NULL)
	{
		*new = data->tk_list;
		*new_head = *new;
	}
	else
	{
		(*new)->next = data->tk_list;
		*new = (*new)->next;
	}
}

t_list	*list_no_redirection(t_data *data)
{
	t_list	*new;
	t_list	*new_head;
	t_token	*token;

	new = NULL;
	new_head = new;
	while (data->tk_list)
	{
		token = data->tk_list->content;
		if (token->type == CHAR_GREATER || token->type == CHAR_APPEND
			|| token->type == CHAR_LESSER || token->type == CHAR_HEREDOC)
			data->tk_list = data->tk_list->next;
		else
			copy_list(data, &new, &new_head);
		data->tk_list = data->tk_list->next;
	}
	new->next = NULL;
	return (new_head);
}

t_list	*clear_redirection(t_data *data)
{
	t_list	*new_head;

	if (data->tk_list == NULL)
		return (NULL);
	new_head = list_no_redirection(data);
	return (new_head);
}

void	store_redirection(t_data *data)
{
	t_list	*new;

	init_io(data);
	store_infile(data);
	store_outfile(data);
	new = clear_redirection(data);
	ft_lstclear(&(data->tk_list), free);
	data->tk_list = new;
}

