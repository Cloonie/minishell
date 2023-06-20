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

void	get_token(char **input)
{
	int			i;
	int			j;
	const char	*operators;

	operators = "\"\'><$|";
	i = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (ft_strchr(operators, input[i][j]) != NULL)
			{
				if (input[i][j] == '\"')
					printf("DOUBLEQUOTE\n");
				else if (input[i][j] == '\'')
					printf("SINGLEQUOTE\n");
				else if (input[i][j] == '<')
					printf("LEFTARROW\n");
				else if (input[i][j] == '>')
					printf("RIGHTARROW\n");
				else if (input[i][j] == '$')
					printf("DOLLAR\n");
				else if (input[i][j] == '|')
					printf("PIPE\n");
			}
			j++;
		}
		i++;
	}
}

char	**get_input(char *cwd, char **envp)
{
	char	*line;
	char	**input;

	line = readline(ft_strjoin(ft_strjoin
				("\033[38;5;39m[minishell] \033[4;36m", cwd),
				"\033[0;36m> \033[0m"));
	if (line == NULL)
		exit(0);
	ft_strtrim(line, " ");
	add_history(line);
	input = lexer(line);
	get_token(input);
	remove_quotes(input);
	check_dollar(input, envp);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	cwd[1024];

	g_ms = malloc(sizeof(t_minishell));
	if (!argv[0] || argc != 1)
		myexit(1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		getcwd(cwd, sizeof(cwd));
		g_ms->input = get_input(cwd, envp);
		cmd(g_ms->input, cwd, envp);
		// printf("VAR: %s TOKEN: %d QUOTED: %d\n", list->var, list->token, list->quoted);
		// printf("%s", list->var);
	}
}