/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:44:54 by llai              #+#    #+#             */
/*   Updated: 2024/03/19 23:05:56 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>

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

typedef struct s_token
{
	int		type;
	char	*data;
}	t_token;

// typedef struct s_tk_node{
// 	char				*token;
// 	struct s_tk_node	*next;
// } t_tk_node;
//
typedef enum
{
	NODE_PIPE = (1 << 0),
	NODE_BCKGRND 		= (1 << 1),
    NODE_SEQ 			= (1 << 2),
    NODE_REDIRECT_IN 	= (1 << 3),
    NODE_REDIRECT_OUT 	= (1 << 4),
    NODE_CMDPATH		= (1 << 5),
    NODE_ARGUMENT		= (1 << 6),

    NODE_DATA 			= (1 << 7),
}	NodeType;

typedef struct s_ast
{
	int				type;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_data
{
	char	*inputString;
	t_list	*tk_list;
	t_list	*cur_token;
	t_ast	*ast;
}	t_data;

void	ignore_control_key();
void	printDir();
int		takeInput(t_data *data);
// void	tokenize(char *cmd_line, t_list **tk_list);
void	tokenize(t_data *data);
// int		parse(t_list *token_list, t_ast **syntax_tree);
int		parse(t_data *data);
void	astAttachBinaryBranch(t_ast *root, t_ast *leftNode, t_ast *rightNode);
void	astNodeSetType(t_ast *node, NodeType nodetype);
void	astNodeSetData(t_ast *node, char *data);
void	astNodeDelete(t_ast *node);


void printTree(t_ast* root);

#endif // !MINISHELL_H
