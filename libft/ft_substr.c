/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:28:05 by llai              #+#    #+#             */
/*   Updated: 2023/11/05 18:14:47 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It takes a substring from the given s 
 *  starting with start and ending with len characters.
 *  The new string will be allocated with memory.
 *
 *  Return value:
 *  A pointer to the new string.
 *  NULL if the memory allocation fails.
 */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	result_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	s += start;
	if (ft_strlen(s) < len)
		result_len = ft_strlen(s) + 1;
	else
		result_len = len + 1;
	ptr = malloc(result_len * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, result_len);
	return (ptr);
}
