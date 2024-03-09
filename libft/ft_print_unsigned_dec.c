/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_dec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:20:31 by llai              #+#    #+#             */
/*   Updated: 2023/12/19 08:21:22 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*  ft_ulen: Takes an unsigned integer,                                       */
/*           Returns 1 if it is zero.                                         */
/*           Otherwise, returns the length of the integer.                    */
/* ************************************************************************** */
static size_t	ft_ulen(unsigned int num);

/* ************************************************************************** */
/*  ft_u_to_str: Takes an unsigned integer and the length of the integer      */
/*           Returns NULL if the memory allocation failed.                    */
/*           Otherwise, returns the string of the unsigned integer.           */
/* ************************************************************************** */
static char		*ft_u_to_str(unsigned int num, size_t len);

/* ************************************************************************** */
/*  ft_print_unsigned_dec: Takes an unsigned integer,                         */
/*                         converts it to a string and output on stdout.      */
/*                         Returns the count of the string.                   */
/* ************************************************************************** */
int	ft_print_unsigned_dec(unsigned int n)
{
	int				count;
	size_t			len;
	char			*digit;
	unsigned int	num;

	count = 0;
	num = (unsigned int)n;
	len = ft_ulen(num);
	digit = ft_u_to_str(num, len);
	count = ft_print_str(digit);
	free(digit);
	return (count);
}

static size_t	ft_ulen(unsigned int num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static char	*ft_u_to_str(unsigned int num, size_t len)
{
	unsigned int	n;
	char			*u_ptr;
	int				mod;

	n = num;
	u_ptr = ft_calloc((len + 1), sizeof(char));
	if (!u_ptr)
		return (NULL);
	u_ptr[len] = '\0';
	len--;
	while (len != (size_t)-1)
	{
		mod = n % 10;
		u_ptr[len] = mod + '0';
		n /= 10;
		len--;
	}
	return (u_ptr);
}
