/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:32:33 by llai              #+#    #+#             */
/*   Updated: 2023/11/02 21:12:04 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *  Description:
 *  It checks if c is alphabetic.
 *
 *  Return value:
 *  Non-zero if c is alphabetic, zero if not.
 *
 */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (c);
	return (0);
}
