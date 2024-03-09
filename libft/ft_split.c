/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:34:01 by llai              #+#    #+#             */
/*   Updated: 2023/11/05 18:16:33 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It creates an array of strings 
 *  by splitting the string s with the seperator c.
 *
 *  Return value:
 *  A pointer to the array of strings.
 *  NULL if the memory allocation fails.
 */

static int	count_string(char const *s, char sep)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == sep)
			s++;
		if (*s != sep && *s != '\0')
			count++;
		while (*s != sep && *s != '\0')
			s++;
	}
	return (count);
}

static char	*extract_word(char const *s, char sep)
{
	int		len;
	int		i;
	char	*word;

	i = 0;
	len = 0;
	while (s[i] != '\0' && s[i] != sep)
	{
		len++;
		i++;
	}
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	arr = malloc((count_string(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			arr[i] = extract_word(s, c);
			i++;
		}
		while (*s != c && *s != '\0')
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
