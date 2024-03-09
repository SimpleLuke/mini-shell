/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:22:25 by llai              #+#    #+#             */
/*   Updated: 2023/12/19 08:21:13 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/*  ft_print_str: Takes a string (a pointer to a constant char).              */
/*                Output (null) if there is no string,                        */
/*                Otherwise, output the string.                               */
/*                Returns the count of the string.                            */
/* ************************************************************************** */

int	ft_print_str(const char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*str != '\0')
	{
		write(1, str, 1);
		count++;
		str++;
	}
	return (count);
}
