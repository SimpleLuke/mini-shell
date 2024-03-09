/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:45:07 by llai              #+#    #+#             */
/*   Updated: 2023/12/19 08:21:03 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*  ft_print_memory: Takes an unsigned long integer,                          */
/*                   Prints the 0x prefix and call ft_print_address           */
/*                   to print address in hexadecimal.                         */
/*                   Returns the count of the 0x plus hexadeciaml address.    */
/* ************************************************************************** */
static int	ft_print_memory(unsigned long int n);

/* ************************************************************************** */
/*  ft_print_address: Takes an unsigned long integer,                         */
/*                    prints the unsigned long integer in                     */
/*                    hexadecimal format.                                     */
/*                    Returns the count of the hexadeciaml address.           */
/* ************************************************************************** */
static void	ft_print_address(unsigned long int n);

/* ************************************************************************** */
/*  ft_ptr_len: Takes an unsigned long integer,                               */
/*              Returns 1 if it is zero.                                      */
/*              Otherwise, returns the length of the hexadeciaml integer.     */
/* ************************************************************************** */
static int	ft_ptr_len(unsigned long int n);

/* ************************************************************************** */
/*  ft_print_ptr: Takes an unsigned long integer,                             */
/*                output null pointer if it is zero.                          */
/*                Otherwise, it outputs hexadecimal format.                   */
/*                Returns the count of the output string.                     */
/* ************************************************************************** */
int	ft_print_ptr(unsigned long int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count += ft_print_str(PTRNULL);
		return (count);
	}
	else
		count += ft_print_memory(n);
	return (count);
}

static int	ft_print_memory(unsigned long int n)
{
	int	count;

	count = 0;
	count += ft_print_str("0x");
	ft_print_address(n);
	count += ft_ptr_len(n);
	return (count);
}

static void	ft_print_address(unsigned long int n)
{
	if (n >= 16)
	{
		ft_print_address(n / 16);
		ft_print_address(n % 16);
	}
	else
	{
		if (n < 10)
			ft_print_c(n + '0');
		else if (n >= 10)
			ft_print_c((n - 10) + 'a');
	}
}

static int	ft_ptr_len(unsigned long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		len++;
		n /= 16;
	}
	return (len);
}
