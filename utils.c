/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 00:07:08 by mliew             #+#    #+#             */
/*   Updated: 2023/04/04 00:07:08 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	myexit(int status)
{

	if (status == EXIT_SUCCESS)
		printf("EXIT_SUCCESS\n");
	else if (status == EXIT_FAILURE)
		printf("EXIT_FAILURE\n");
	system("leaks minishell");
	exit(status);
}

enum {
	TOK_EOF,
	TOK_CMD,
	TOK_ARG,
	TOK_BACKSLASH,
	TOK_SEMICOLON,
	TOK_SINGLEQ,
	TOK_DOUBLEQ,
	TOK_DOLLAR,
	TOK_REDIRECT_LEFT,
	TOK_REDIRECT_RIGHT,
	TOK_APPEND_LEFT,
	TOK_APPEND_RIGHT,
	TOK_PIPE,
};

int	token_cmd(char *str)
{
	if (ft_strncmp(str, "echo\0", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "cd\0", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd\0", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "export\0", 7) == 0)
		return (1);
	else if (ft_strncmp(str, "unset\0", 6) == 0)
		return (1);
	else if ((ft_strncmp(str, "env\0", 4) == 0))
		return (1);
	else if (ft_strncmp(str, "exit\0", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "./", 2) == 0
		|| ft_strncmp(str, "/", 1) == 0)
		return (1);
	// else if (executable(input, envp))
	// 	return (1);
	return (0);
}

int	tokenize(char *str)
{
	while (*str)
	{
		// if (*str == '\"')
		// 	list->quoted = 2;
		// else if (*str == '\'')
		// 	list->quoted = 1;
		// else
		// 	list->quoted = 0;
		if (!str)
			return (TOK_EOF);
		else if (*str == '>')
			return (TOK_REDIRECT_RIGHT);
		else if (*str == '<')
			return (TOK_REDIRECT_LEFT);
		else if (*str == '$')
			return (TOK_DOLLAR);
		else if (*str == '|')
			return (TOK_PIPE);
		else if (token_cmd(str))
			return (TOK_CMD);
		str++;
	}
	return (0);
}