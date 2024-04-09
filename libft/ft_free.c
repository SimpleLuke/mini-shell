/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:56:42 by llai              #+#    #+#             */
/*   Updated: 2024/04/09 11:32:34 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_free_strarr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	ft_lstdelone2(t_list *lst, void (*del)(void **))
{
	if (!lst)
		return ;
	if (del)
		del(lst -> content);
	free(lst);
	lst = NULL;
}

void	ft_lstclear2(t_list **lst, void (*del)(void **))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)-> next;
		ft_lstdelone2(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
