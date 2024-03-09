/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:39:55 by llai              #+#    #+#             */
/*   Updated: 2023/11/07 09:13:13 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
 *  Description:
 *  It converts the integer n into a string.
 *
 *  Return value:
 *  A pointer string of the integer.
 */

static size_t	ft_numlen(long num)
{
	size_t	count;

	count = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		count++;
		num = -num;
	}
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

static char	*ft_num_to_str(size_t len, char *result, long n)
{
	result = ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	result[len] = '\0';
	len--;
	while (len)
	{
		result[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	if (result[0] != '-')
		result[0] = (n % 10) + '0';
	return (result);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	num;
	char	*result;

	num = n;
	len = ft_numlen(num);
	result = NULL;
	result = ft_num_to_str(len, result, num);
	if (!result)
		return (NULL);
	return (result);
}
