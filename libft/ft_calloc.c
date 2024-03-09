/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:58:19 by llai              #+#    #+#             */
/*   Updated: 2023/11/02 20:25:44 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It allocates enough memory for nmemb elements of size bytes each
 *  and filled with bytes of value zero.
 *
 *  Return value:
 *  A pointer to the allocated memory. NULL if the memory allocation fails.
 */

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	res;

	res = nmemb * size;
	if (size != 0 && (res / size != nmemb))
		return (NULL);
	ptr = malloc(res);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, res);
	return (ptr);
}
