/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:58:26 by llai              #+#    #+#             */
/*   Updated: 2023/11/02 20:39:49 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It locates the first occurrence of c in the string s.
 *
 *  Return value:
 *  A pointer to the located character.
 *  NULL if the character does not appear in the string.
 */

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)(s));
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)(s));
	return (NULL);
}
