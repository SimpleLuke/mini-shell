/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:39:36 by llai              #+#    #+#             */
/*   Updated: 2023/12/19 08:53:11 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
 *  Description:
 *  It converts a string into an long.
 *
 *  Return value:
 *  A converted long.
 *  0 if invalid digit.
 */

long	ft_atol(const char *nptr)
{
	long	num;
	int		is_neg;
	int		i;

	num = 0;
	is_neg = 1;
	i = 0;
	while (nptr[i] && (nptr[i] == ' ' || nptr[i] == '\t'
			|| nptr[i] == '\n' || nptr[i] == '\v'
			|| nptr[i] == '\r' || nptr[i] == '\f'))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		is_neg *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (num * is_neg);
}
