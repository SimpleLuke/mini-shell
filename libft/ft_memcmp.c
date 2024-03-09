/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:12:16 by llai              #+#    #+#             */
/*   Updated: 2023/11/05 18:12:19 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It compares the byte string s1 against byte string s2.
 *  Both strings are assumed to be n bytes long.
 *
 *  Return value:
 *  An integer greater than, equal to, or less than 0
 *  if the string s1 is greater than, equal to, or less than the string s2.
 */

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ptr1;
	const char	*ptr2;

	ptr1 = (const char *)s1;
	ptr2 = (const char *)s2;
	if (n == 0)
		return (0);
	while (*ptr1 == *ptr2 && n > 1)
	{
		ptr1++;
		ptr2++;
		n--;
	}
	return ((unsigned char)*ptr1 - (unsigned char)*ptr2);
}
