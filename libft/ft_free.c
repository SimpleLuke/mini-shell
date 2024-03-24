/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:56:42 by llai              #+#    #+#             */
/*   Updated: 2024/03/24 16:23:52 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
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
