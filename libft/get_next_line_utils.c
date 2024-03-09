/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:30:52 by llai              #+#    #+#             */
/*   Updated: 2024/01/04 17:48:07 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************************************************************
 * Summary of File:
 *
 * 	This file contains helper functions for the get_next_line function.
 * 	The functions are mostly from libft and/or standard C library.
 *
 * **************************************************************************/
#include "get_next_line.h"

// size_t	ft_strlen(const char *str);
// char	*ft_strchr(char *str, char c);
// size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
// char	*ft_strdup(const char *str);
// char	*ft_strjoin(char *s1, const char *s2, size_t len);

/* **************************************************************************
 * size_t	ft_strlen(const char *str)
 *
 * Summary of the function:
 * 
 * 		This function counts the length of the string.
 * 
 * Parameters: A pointer to a constant char.
 *
 * Return value: The length of the string.
 * **************************************************************************/
size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

/* **************************************************************************
 * char	*strchr(char *str, char c)
 *
 * Summary of the function:
 * 
 * 		This function locates the first occurrence of c in the string.
 * 
 * Parameters: A pointer to a string character and a charater occurrence.
 *
 * Return value: 
 * 		A pointer to the located character.
 *		Null if the character does not appear in the string.
 * **************************************************************************/
char	*ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

/* **************************************************************************
 * size_t ft_strlcpy(char *dest, const char *src, size_t dest_size)
 *
 * Summary of the function:
 *
 * 		This function copies from src to dest for dest_size - 1.
 * 		It makes sure the dest string always null-terminated.
 * 
 * Parameters: 
 * 		A pointer to the destination string, the source string and
 * 		the destination size to copy.
 *
 * Return value: 
 *		The total length of the string tried to create.
 *		The lenth of the src.
 * **************************************************************************/
size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	src_size;
	size_t	i;

	src_size = ft_strlen(src);
	i = 0;
	if (dest_size > 0)
	{
		while (i < src_size && i < dest_size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_size);
}

/* **************************************************************************
 * char *ft_strjoin(char *s1, const char *s2, size_t len)
 *
 * Summary of the function:
 *
 * 		This function concatenates the s1 and s2.
 * 		It allocates new memory for the joined string.
 * 
 * Parameters: 
 * 		A pointer to string1 and string2 and the length of string2.
 *
 * Return value: 
 *		A pointer to the first character of the newly joined string.
 * **************************************************************************/
char	*ft_strjoin(char *s1, const char *s2, size_t len)
{
	int		s1_size;
	int		s2_size;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = len;
	str = malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_size + 1);
	ft_strlcpy((str + s1_size), s2, s2_size + 1);
	free(s1);
	return (str);
}

/* **************************************************************************
 * char *ft_strdup(const char *str)
 *
 * Summary of the function:
 *
 * 		This function duplicates the string.
 * 		It allocates new memory for the duplicated string.
 * 
 * Parameters: 
 * 		A pointer to a string.
 *
 * Return value: 
 *		A pointer to the first character of the newly duplicated string.
 * **************************************************************************/
char	*ft_strdup(const char *str)
{
	char	*copy;
	int		str_size;

	str_size = ft_strlen(str);
	copy = malloc(sizeof(char) * (str_size + 1));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, str, str_size + 1);
	return (copy);
}
