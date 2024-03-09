/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:35:44 by llai              #+#    #+#             */
/*   Updated: 2023/11/02 20:40:04 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It allocateds sufficient memory for a copy of the string s,
 *  does the copy and returns a pointer to it.
 *
 *  Return value:
 *  A pointer to the new string. NULL if the memory allocation fails.
 */

char	*ft_strdup(const char *s)
{
	int		len;
	char	*ptr;

	len = ft_strlen(s) + 1;
	ptr = malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len);
	return (ptr);
}
