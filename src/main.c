/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:08:51 by llai              #+#    #+#             */
/*   Updated: 2024/03/19 19:23:09 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_node(t_list *tk_list)
{
	t_token	*data;

	while (tk_list != NULL)
	{
		data = (t_token *)tk_list->content;
		printf("type: %d\n", data->type);
		printf("data: %s\n", data->data);
		tk_list = tk_list->next;
	}
}

void	init_data(t_data *data)
{
	data->inputString = NULL;
	data->tk_list = NULL;
}

int main()
{
	t_data	data;
	// char	*inputString;
	// t_list	*tk_list = NULL;
	// t_ASTNode	*exectree;

	init_data(&data);
	ignore_control_key();
	while (1)
	{
		// printDir();
		if (takeInput(&data))
			continue;
		// printf("%s\n", inputString);
		tokenize(&data);
		print_node(data.tk_list);
		// parse(tk_list, &exectree);
		ft_lstclear(&(data.tk_list), free);
		// printf("%s\n", (char *)tk_list->content);

		// ft_lstiter(tk_list, (void *)print_node);
	}
	return (0);
}
