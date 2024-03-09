/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:31:03 by llai              #+#    #+#             */
/*   Updated: 2023/12/19 08:23:28 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*  ft_print_digit: Takes an integer and convert it to a string.              */
/*                  Output the string on stdout.                              */
/*                  Returns the count of the string.                          */
/* ************************************************************************** */
int	ft_print_digit(int n)
{
	int		count;
	char	*digit;

	count = 0;
	digit = ft_itoa(n);
	count = ft_print_str(digit);
	free(digit);
	return (count);
}
