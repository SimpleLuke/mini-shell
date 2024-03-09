/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:27:53 by llai              #+#    #+#             */
/*   Updated: 2023/11/02 21:15:48 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *  Description:
 *  It checks if c is printable character.
 *
 *  Return value:
 *  Non-zero if c is printable character, zero if not.
 *
 */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (c);
	return (0);
}
