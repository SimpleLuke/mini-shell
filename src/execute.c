/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:34:15 by llai              #+#    #+#             */
/*   Updated: 2024/04/05 13:20:23 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_simple_cmd(t_ast *node, t_data *data, bool async)
{
	(void) async;
	init_cmd(node, data);
	execute_cmd(node, data);
}

void	execute_cmdpath(t_ast *node, t_data *data, bool async)
{
	if (node == NULL)
		return ;
	if (NODETYPE(node->type) == NODE_CMDPATH)
	{
		execute_simple_cmd(node, data, async);
	}
}

void	execute_job(t_ast *node, t_data *data, bool async)
{
	(void)async;
	if (node == NULL)
		return ;
	if (NODETYPE(node->type) == NODE_PIPE)
	{
		printf("PIPE\n");
	}
	else if (NODETYPE(node->type) == NODE_CMDPATH)
	{
		execute_cmdpath(node, data, async);
	}

}

void	execute_tree(t_data *data)
{
	execute_job(data->ast, data, false);
}
