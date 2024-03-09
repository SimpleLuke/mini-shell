/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:37:23 by llai              #+#    #+#             */
/*   Updated: 2023/11/05 18:16:00 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
 *  Description:
 *  It appends string src to the end of dst.
 *  At most size - strlen(dst) - 1 characters.
 *  It will Nul-terminate, unless size is 0 
 *  or the original dst string was longer than size.
 *
 *  Return value:
 *  The total length of the string they tried to create.
 *  The initial length of dst + the length of src.
 *
 */

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] != '\0' && (i + dst_len) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
