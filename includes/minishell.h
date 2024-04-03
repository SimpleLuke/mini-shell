/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:44:54 by llai              #+#    #+#             */
/*   Updated: 2024/04/03 14:34:18 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h> 
# include <signal.h>
# include <stdbool.h>

# define MAXCOM 1000
# define MAXLIST 100

enum e_TokenType
{
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
	CHAR_APPEND = 1,
	CHAR_HEREDOC = 2,
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	CHAR_DOLLAR = '$',
	TOKEN	= -1,
};

enum
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
	STATE_IN_DOLLAR
};

typedef struct s_token
{
	int		type;
	char	*data;
}	t_token;

typedef struct s_infile
{
	int		idx;
	int		type;
	char	*name;
}	t_infile;

typedef struct s_outfile
{
	int		idx;
	int		type;
	char	*name;
}	t_outfile;

typedef struct s_io
{
	int			in_size;
	int			out_size;
	t_infile	*infile_list;
	t_outfile	*outfile_list;
}	t_io;

typedef enum e_NodeType
{
	NODE_PIPE = (1 << 0),
	NODE_BCKGRND = (1 << 1),
	NODE_SEQ = (1 << 2),
	NODE_REDIRECT_IN = (1 << 3),
	NODE_REDIRECT_OUT = (1 << 4),
	NODE_CMDPATH = (1 << 5),
	NODE_ARGUMENT = (-1 << 6),
	NODE_REDIRECT_APPREND = (1 << 7),
	NODE_REDIRECT_HEREDOC = (1 << 8),
	NODE_DATA = (1 << 9),
}	t_NodeType;

typedef struct s_ast
{
	int				type;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_tokenizer
{
	int		state;
	int		i;
	int		chtype;
	t_list	*tmp;

}	t_tokenizer;

typedef struct s_data
{
	char	*input_string;
	char	**env_list;
	t_list	*tk_list;
	t_io	io;
	t_list	*cur_token;
	t_ast	*ast;
}	t_data;

void	ignore_control_key(void);
int		take_input(t_data *data);
// void	tokenize(char *cmd_line, t_list **tk_list);
void	tokenize(t_data *data);
// int		parse(t_list *token_list, t_ast **syntax_tree);
int		parse(t_data *data);
void	ast_attach_binary_branch(t_ast *root, t_ast *leftNode, t_ast *rightNode);
void	ast_node_set_type(t_ast *node, t_NodeType nodetype);
void	ast_node_set_data(t_ast *node, char *data);
void	ast_node_delete(t_ast *node);

void	printTree(t_ast *root);
void	printDir(void);
void	print_node(t_list *tk_list);
char	**copy_string_list(char **list);
char	*convert_token(char *token, t_data *data);
char	*convert_dqtoken(char *token, t_data *data);

// expander.c
void	add_dquote(t_ast *ast);
void	expand_quote(t_ast *ast);
void	expand_dquote(t_ast *ast, t_data *data);
char	*convert_quote(char *data);
char	*convert_dquote(char *str, t_data *data);
void	expand_token(t_ast *ast, t_data *data);

// builtins.c
void	pwd(void);
void	echo(bool newline, char *str);
int		cd(char *arg);
void	env(char **envp);
void	export_var(char *arg, char ***env_list);
void	unset_env(char *arg, char ***env_list);
void	exit_shell(void);
int		exist_var(char *arg, char *str, int *is_exist);
char	*get_envvar(char *arg, t_data *data);

#endif // !MINISHELL_H
