/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:44:54 by llai              #+#    #+#             */
/*   Updated: 2024/03/13 16:08:22 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#define MAXCOM 1000
#define MAXLIST 100

typedef struct s_tk_node{
	char				*token;
	struct s_tk_node	*next;
} t_tk_node;

void	ignore_control_key();
void	printDir();
int		takeInput(char **str);
void	tokenize(char *cmd_line, t_list **tk_list);

#endif // !MINISHELL_H
