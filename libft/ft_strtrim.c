/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:30:06 by llai              #+#    #+#             */
/*   Updated: 2023/11/05 18:14:26 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It removes any characters of the set 
 *  from the beginning and the end of the string s1.
 *  The new trimmed string will be allocated with memory.
 *
 *  Return value:
 *  A pointer to the new trimmed string.
 *  NULL if the memory allocation fails.
 */

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	if (!ft_strlen(s1))
		return (ft_strdup(""));
	if (!ft_strlen(set))
		return (ft_strdup(s1));
	while (is_set(s1[i++], set))
		start++;
	i = ft_strlen(s1) - 1;
	while (is_set(s1[i--], set))
		end++;
	return (ft_substr(s1, start, ft_strlen(s1) - start - end));
}
