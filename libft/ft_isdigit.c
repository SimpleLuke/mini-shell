/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:42:52 by llai              #+#    #+#             */
/*   Updated: 2023/11/02 21:12:42 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *  Description:
 *  It checks if c is digit.
 *
 *  Return value:
 *  Non-zero if c is digit, zero if not.
 *
 */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}
