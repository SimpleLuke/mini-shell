/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:43:25 by llai              #+#    #+#             */
/*   Updated: 2024/03/09 20:17:44 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

// Function to print Current Directory
void	printDir()
{
	char	cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("llai:%s", cwd);
}

// Function to take input
int	takeInput(char *str)
{
	char	*buf;

	rl_catch_signals = 0;
	buf = readline("$ ");
	if (!buf)
	{
		printf("exit\n");
		exit(0);
	}
	else if (ft_strlen(buf) != 0)
	{
		add_history(buf);
		ft_strlcpy(str, buf, sizeof(buf));
		free(buf);
		return (0);
	}
	else if (!buf)
	{
		printf("Exit");
		exit(0);
	}
	else	
		return (1);
}

void	signint_handler(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	printDir();
	rl_on_new_line();
	rl_redisplay();
}

void	ignore_control_key()
{
	signal(SIGINT, signint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
