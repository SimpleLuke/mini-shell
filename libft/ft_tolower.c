/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:32:17 by llai              #+#    #+#             */
/*   Updated: 2023/10/31 21:34:56 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *  Description:
 *  It converts a upper-case letter to the corresponding lower-case letter.
 *
 *  Return value:
 *  The corresponding lower-case letter if there is one.
 *  Otherwise, c is returned unchanged.
 */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
