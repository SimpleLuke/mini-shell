/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:44:54 by llai              #+#    #+#             */
/*   Updated: 2024/03/14 16:47:25 by llai             ###   ########.fr       */
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

enum TokenType{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	
	TOKEN	= -1,
};

enum {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
};

typedef struct s_tk_node{
	char				*token;
	struct s_tk_node	*next;
} t_tk_node;

void	ignore_control_key();
void	printDir();
int		takeInput(char **str);
void	tokenize(char *cmd_line, t_list **tk_list);

#endif // !MINISHELL_H
