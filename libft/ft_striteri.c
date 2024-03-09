/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:37:15 by llai              #+#    #+#             */
/*   Updated: 2023/11/05 18:15:13 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *  Description:
 *  It applies the function f to each character in the string s.
 *  Passing the index as the first argument 
 *  and the address of the character as second argument
 *  in the function f.
 *
 *  Return value:
 *  None.
 */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &(s[i]));
		i++;
	}
}
