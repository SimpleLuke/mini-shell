/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:45:16 by llai              #+#    #+#             */
/*   Updated: 2023/11/05 18:13:53 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It copies n bytes from from memory area string src to area dest.
 *  The memory area may overlap. 
 *  The copy is always done in a non-desstructive manner.
 *  If the dest is found within src pointer and index n,
 *  copying will be done from back to front. Otherwise, front to back.
 *
 *  Return value:
 *  A pointer to dest.
 *
 */

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;

	if (src == dest)
		return (dest);
	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	if (src_ptr < dest_ptr && (src_ptr + n) > dest_ptr)
		while (n--)
			*(dest_ptr + n) = *(src_ptr + n);
	else
		while (n--)
			*dest_ptr++ = *src_ptr++;
	return (dest);
}
