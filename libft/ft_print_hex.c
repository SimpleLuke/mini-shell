/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:15 by llai              #+#    #+#             */
/*   Updated: 2023/12/19 08:20:52 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*  ft_hexlen: Takes an unsigned integer                                      */
/*             Returns the length of the hexadecimal number                   */
/* ************************************************************************** */
static size_t	ft_hexlen(unsigned int num);

/* ************************************************************************** */
/*  ft_hex_to_str: Takes an unsigned integer,                                 */
/*                 allocate memory for the length of the integer              */
/*                 Returns a hexadecimal string depends on isupper or not     */
/* ************************************************************************** */
static char		*ft_hex_to_str(unsigned int num, size_t len, int isupper);

/* ************************************************************************** */
/*  ft_print_hex: Takes an unsigned integer and depends if it is upper case,  */
/*                convert the integer to hexadecimal.                         */
/*                Output hexadecimal string on stdout.                        */
/*                Returns the count of the string.                            */
/* ************************************************************************** */
int	ft_print_hex(unsigned int n, int isupper)
{
	int					count;
	size_t				len;
	char				*hex;
	unsigned int		num;

	count = 0;
	num = (unsigned int)n;
	len = ft_hexlen(num);
	hex = NULL;
	hex = ft_hex_to_str(num, len, isupper);
	count = ft_print_str(hex);
	free(hex);
	return (count);
}

static size_t	ft_hexlen(unsigned int num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= 16;
	}
	return (len);
}

static char	*ft_hex_to_str(unsigned int num, size_t len, int isupper)
{
	long	n;
	char	*hex_ptr;
	int		mod;

	n = num;
	hex_ptr = ft_calloc((len + 1), sizeof(char));
	if (!hex_ptr)
		return (NULL);
	hex_ptr[len] = '\0';
	len--;
	while (len != (size_t)-1)
	{
		mod = n % 16;
		if (isupper)
			hex_ptr[len] = "0123456789ABCDEF"[mod];
		else
			hex_ptr[len] = "0123456789abcdef"[mod];
		n /= 16;
		len--;
	}
	return (hex_ptr);
}
