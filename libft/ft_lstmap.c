/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:56:35 by llai              #+#    #+#             */
/*   Updated: 2023/11/08 15:05:18 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * 	Description:
 * 	It creates a new list with applying function to the content
 * 	in the old list.
 * 	If memory allocation fails, the new list will be deleted
 * 	and be freed.
 *
 * 	Return value;
 * 	A new list containing new content values.
 * 	NULL if the memory allocation failed.
 */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*temp;

	if (!lst)
		return (NULL);
	head = NULL;
	temp = NULL;
	while (lst)
	{
		if (!f)
			temp = ft_lstnew(lst -> content);
		else
			temp = ft_lstnew(f(lst -> content));
		if (!temp)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, temp);
		lst = lst -> next;
	}
	return (head);
}
