/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:30:52 by llai              #+#    #+#             */
/*   Updated: 2024/01/04 17:49:22 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* **************************************************************************
 * char	*get_next_line(int fd)
 *
 * Summary of the function:
 * 
 * 		This function reads the file with the BUFFER_SIZE until it
 * 		encounters a newline or reaches the EOF.
 * 		Line keeps track to the previous stored string and the newly
 * 		joined string.
 * 		Then it copies what after the newline to the static buffer.
 * 		The static buffer stores the string for the next call.
 * 		And null-terminating the line before the newline.
 * 
 * Parameters: A file descriptor.
 *
 * Return value: A pointer to the line.
 * **************************************************************************/
// char	*get_next_line(int fd);

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
// size_t	ft_strlen(const char *str);

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
// char	*ft_strchr(char *str, char c);

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
// size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);

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
char	*ft_strjoin_gnl(char *s1, const char *s2, size_t len);

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
// char	*ft_strdup(const char *str);

#endif
