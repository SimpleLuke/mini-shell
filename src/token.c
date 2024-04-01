/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:08:50 by llai              #+#    #+#             */
/*   Updated: 2024/04/01 12:57:12 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	getchartype(char c)
{
	if (c == '\'')
		return (CHAR_QOUTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == '\\')
		return (CHAR_ESCAPESEQUENCE);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == '\0')
		return (CHAR_NULL);
	else if (c == '$')
		return (CHAR_DOLLAR);
	else
		return (CHAR_GENERAL);
}

void	tmp_to_tokens(t_data *data, t_list *tmp, int type)
{
	int		size;
	int		i;
	char	*tokenstr;
	t_token	*token;

	i = 0;
	if (tmp == NULL)
		return ;
	size = ft_lstsize(tmp);
	tokenstr = malloc((size + 1) * sizeof(char));
	while (i < size)
	{
		tokenstr[i] = *(char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	tokenstr[i] = '\0';
	token = (t_token *)malloc(sizeof(t_token));
	token->data = tokenstr;
	token->type = type;
	ft_lstadd_back(&data->tk_list, ft_lstnew(token));
}

int	ft_isfilename(char c)
{
	if (c == '#' || c == '%' || c == '+' || c == ',' || c == '-'
		|| c == '.' || c == '/' || c == ':' || c == '?' || c == '@'
		|| c == 92 || c == '^' || c == 94 || c == 96 || c == '{'
		|| c == '}' || c == '~')
		return (1);
	return (0);
}

void	quote_in_general(int *state, int *i, t_list **tmp, t_data *data)
{
	*state = STATE_IN_QUOTE;
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
}

void	dquote_in_general(int *state, int *i, t_list **tmp, t_data *data)
{
	*state = STATE_IN_DQUOTE;
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
}

void	escape_in_general(int *i, t_list **tmp, t_data *data)
{
	*i += 1;
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
}

void	char_in_general(int *i, t_list **tmp, t_data *data)
{
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
}

void	dollar_in_general(int *i, t_list **tmp, t_data *data)
{
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
}

void	append_in_general(int *i, t_list **tmp, t_data *data)
{
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
	*i += 1;
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
	tmp_to_tokens(data, *tmp, CHAR_APPEND);
	ft_lstclear(tmp, free);
	*i += 1;
}

void	heredoc_in_general(int *i, t_list **tmp, t_data *data)
{
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
	*i += 1;
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
	tmp_to_tokens(data, *tmp, CHAR_HEREDOC);
	ft_lstclear(tmp, free);
	*i += 1;
}

void	op_in_general(int chtype, int i, t_list **tmp, t_data *data)
{
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[i]))));
	tmp_to_tokens(data, *tmp, chtype);
	ft_lstclear(tmp, free);
}

void	handle_dquote(int *state, int *i, t_list **tmp, t_data *data)
{
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
	if (data->input_string[*i] == CHAR_DQUOTE)
		*state = STATE_GENERAL;
	else if (data->input_string[*i] == CHAR_NULL)
	{
		tmp_to_tokens(data, *tmp, TOKEN);
		ft_lstclear(tmp, free);
	}
}

void	handle_quote(int *state, int *i, t_list **tmp, t_data *data)
{
	ft_lstadd_back(tmp,
		ft_lstnew(ft_strdup(&(data->input_string[*i]))));
	if (data->input_string[*i] == CHAR_QOUTE)
		*state = STATE_GENERAL;
	else if (data->input_string[*i] == CHAR_NULL)
	{
		tmp_to_tokens(data, *tmp, TOKEN);
		ft_lstclear(tmp, free);
	}
}

void	tokenize_and_free(t_data *data, t_list **tmp)
{
	if (tmp != NULL)
	{
		tmp_to_tokens(data, *tmp, TOKEN);
		ft_lstclear(tmp, free);
	}
}

int	handle_general(t_tokenizer *tker, t_data *data)
{
	if (tker->chtype == CHAR_QOUTE)
		quote_in_general(&tker->state, &tker->i, &tker->tmp, data);
	else if (tker->chtype == CHAR_DQUOTE)
		dquote_in_general(&tker->state, &tker->i, &tker->tmp, data);
	else if (tker->chtype == CHAR_ESCAPESEQUENCE)
		escape_in_general(&tker->i, &tker->tmp, data);
	else if (tker->chtype == CHAR_GENERAL || tker->chtype == CHAR_DOLLAR)
		char_in_general(&tker->i, &tker->tmp, data);
	else if (tker->chtype == CHAR_GREATER || tker->chtype == CHAR_LESSER
		|| tker->chtype == CHAR_PIPE)
	{
		tokenize_and_free(data, &tker->tmp);
		if (tker->chtype == CHAR_GREATER
			&& data->input_string[tker->i + 1] == CHAR_GREATER)
			return (append_in_general(&tker->i, &tker->tmp, data), 1);
		if (tker->chtype == CHAR_LESSER
			&& data->input_string[tker->i + 1] == CHAR_LESSER)
			return (heredoc_in_general(&tker->i, &tker->tmp, data), 1);
		op_in_general(tker->chtype, tker->i, &tker->tmp, data);
	}
	else if (tker->chtype == CHAR_WHITESPACE
		|| tker->chtype == CHAR_TAB || tker->chtype == CHAR_NULL)
		tokenize_and_free(data, &tker->tmp);
	return (0);
}

void	tokenize(t_data *data)
{
	t_tokenizer	tker;

	tker.i = 0;
	tker.tmp = NULL;
	if (*data->input_string == '\0')
		return ;
	tker.state = STATE_GENERAL;
	while (1)
	{
		tker.chtype = getchartype(data->input_string[tker.i]);
		if (tker.state == STATE_GENERAL)
		{
			if (handle_general(&tker, data))
				continue ;
		}
		else if (tker.state == STATE_IN_DQUOTE)
			handle_dquote(&tker.state, &tker.i, &tker.tmp, data);
		else if (tker.state == STATE_IN_QUOTE)
			handle_quote(&tker.state, &tker.i, &tker.tmp, data);
		if (data->input_string[tker.i] == CHAR_NULL)
			break ;
		tker.i++;
	}
}

void	tmp_to_str(t_list **head, t_list *tmp, int type)
{
	int		size;
	int		i;
	char	*tokenstr;
	t_token	*token;

	i = 0;
	if (tmp == NULL)
		return ;
	size = ft_lstsize(tmp);
	tokenstr = malloc((size + 1) * sizeof(char));
	while (i < size)
	{
		tokenstr[i] = *(char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	tokenstr[i] = '\0';
	// printf("HERE:%s\n", tokenstr);
	token = (t_token *)malloc(sizeof(t_token));
	token->data = tokenstr;
	token->type = type;
	ft_lstadd_back(head, ft_lstnew(token));
}

void	expand_node(t_list *tk_list)
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

char	*expand_strtoken(t_token *token, t_data *data)
{
	char	*str;
	char	*result;
	char	*tmp;
	int		i;
	int		j;

	str = token->data;
	if (str[0] == '$')
	{
		result = get_envvar(str + 1, data);
	}
	else if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
	{
		result = convert_quote(str);
	}
	else if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
	{
		i = 0;
		j = 0;
		tmp = malloc((ft_strlen(str) - 0) * sizeof(char));
		while (str[i])
		{
			if (str[i] != '\"')
			{
				tmp[j] = str[i];
				j++;
			}
			i++;
		}
		tmp[j] = '\0';
		result = convert_token(tmp, data);
	}
	else
	{
		result = ft_strdup(str);
	}
	return (result);
}

void	expanded_list(t_list *lst, t_data *data)
{
	t_token *token;
	char	*new_content;

	while (lst)
	{
		token = lst->content;
		new_content = expand_strtoken(token, data);
		free(token->data);
		token->data = new_content;
		lst = lst->next;
	}

}

char	*convert_token(char *token, t_data *data)
{
	t_tokenizer	tker;
	t_list		*head;
	char		*result;
	t_token		*node;

	tker.i = 0;
	tker.tmp = NULL;
	tker.state = STATE_GENERAL;
	head = NULL;
	while (1)
	{
		tker.chtype = getchartype(token[tker.i]);
		// printf("%s\n", token);
		// printf("%c\n", token[tker.i]);
		if (tker.state == STATE_GENERAL)
		{
			if (tker.chtype == CHAR_QOUTE)
			{
				tmp_to_str(&head, tker.tmp, tker.chtype);
				ft_lstclear(&tker.tmp, free);
				tker.state = STATE_IN_QUOTE;
				ft_lstadd_back(&tker.tmp, ft_lstnew(ft_strdup(&(token[tker.i]))));
			}
			else if (tker.chtype == CHAR_DQUOTE)
			{
				tmp_to_str(&head, tker.tmp, tker.chtype);
				ft_lstclear(&tker.tmp, free);
				tker.state = STATE_IN_DQUOTE;
				ft_lstadd_back(&tker.tmp, ft_lstnew(ft_strdup(&(token[tker.i]))));
			}
			else if (tker.chtype == CHAR_DOLLAR)
			{
				tmp_to_str(&head, tker.tmp, tker.chtype);
				ft_lstclear(&tker.tmp, free);
				tker.state = STATE_IN_DOLLAR;
				ft_lstadd_back(&tker.tmp, ft_lstnew(ft_strdup(&(token[tker.i]))));
			}
			else
			{
				ft_lstadd_back(&tker.tmp, ft_lstnew(ft_strdup(&(token[tker.i]))));
			}
		}
		else if (tker.state == STATE_IN_QUOTE)
		{
			ft_lstadd_back(&tker.tmp, ft_lstnew(ft_strdup(&(token[tker.i]))));
			if (token[tker.i] == CHAR_QOUTE || token[tker.i] == CHAR_NULL)
			{
				tker.state = STATE_GENERAL;
				tmp_to_str(&head, tker.tmp, tker.chtype);
				ft_lstclear(&tker.tmp, free);
			}
		}
		else if (tker.state == STATE_IN_DQUOTE)
		{
			ft_lstadd_back(&tker.tmp, ft_lstnew(ft_strdup(&(token[tker.i]))));
			if (token[tker.i] == CHAR_DQUOTE || token[tker.i] == CHAR_NULL)
			{
				tker.state = STATE_GENERAL;
				tmp_to_str(&head, tker.tmp, tker.chtype);
				ft_lstclear(&tker.tmp, free);
			}
		}
		else if (tker.state == STATE_IN_DOLLAR)
		{
			// ft_lstadd_back(&tker.tmp, ft_lstnew(ft_strdup(&(token[tker.i]))));
			// printf("this=>%c\n", token[tker.i]);
			if (token[tker.i] == CHAR_DQUOTE || token[tker.i] == CHAR_QOUTE || token[tker.i] == CHAR_NULL)
			{
				tker.state = STATE_GENERAL;
				tmp_to_str(&head, tker.tmp, tker.chtype);
				ft_lstclear(&tker.tmp, free);
				continue ;
			}
			ft_lstadd_back(&tker.tmp, ft_lstnew(ft_strdup(&(token[tker.i]))));
		}
		if (token[tker.i] == CHAR_NULL)
		{
			tmp_to_str(&head, tker.tmp, tker.chtype);
			ft_lstclear(&tker.tmp, free);
			break;
		}
		tker.i++;
	}
	print_node(head);
	expanded_list(head, data);
	printf("AFTER=============\n");
	print_node(head);
	result = ft_strdup("");
	while (head)
	{
		node = head->content;
		result = ft_strjoin_gnl(result, node->data, ft_strlen(node->data));
		head = head->next;
	}
	return (result);
}
