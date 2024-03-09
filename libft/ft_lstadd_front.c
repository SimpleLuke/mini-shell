/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:58:03 by llai              #+#    #+#             */
/*   Updated: 2024/01/03 17:37:16 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * 	Description:
 * 	It add new node to the head of the list.
 *
 * 	Return value;
 * 	None.
 */

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	if (!new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	new_node -> next = *lst;
	*lst = new_node;
}
