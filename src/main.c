/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:08:51 by llai              #+#    #+#             */
/*   Updated: 2024/03/13 16:09:50 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_node(t_list *tk_list)
{
	while (tk_list != NULL)
	{
		printf("%s\n", (char *)tk_list->content);
		tk_list = tk_list->next;
	}
}

int main()
{
	char	*inputString;
	t_list	*tk_list = NULL;

	ignore_control_key();
	while (1)
	{
		printDir();
		if (takeInput(&inputString))
			continue;
		// printf("%s\n", inputString);
		tokenize(inputString, &tk_list);
		print_node(tk_list);
		// printf("%s\n", (char *)tk_list->content);

		// ft_lstiter(tk_list, (void *)print_node);
	}
	return (0);
}
