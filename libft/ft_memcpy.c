/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:24:21 by llai              #+#    #+#             */
/*   Updated: 2023/11/05 18:04:44 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
 *  Description:
 *  It copies n bytes from memory area src to memory area dest.
 *  The memory area must not overlap.
 *  Use ft_memmove if the memory area do overlap.
 *
 *  Return value:
 *  A pointer to dest.
 *
 */

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;

	if (!dest && !src)
		return (NULL);
	if (n == 0 || (dest == src))
		return (dest);
	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	while (n-- > 0)
		*dest_ptr++ = *src_ptr++;
	return (dest);
}
