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

void	get_token(t_minishell *ms)
{
	int			i;
	int			j;
	const char	*operators;

	operators = "\"\'><$|";
	i = 0;
	ms->token = malloc(100);
	while (ms->input[i])
	{
		j = 0;
		while (ms->input[i][j])
		{
			if (ft_strchr(operators, ms->input[i][j]) != NULL)
			{
				if (ms->input[i][j] == '\"')
					ms->token[i] = TOK_DOUBLEQ;
				else if (ms->input[i][j] == '\'')
					ms->token[i] = TOK_SINGLEQ;
				else if (ms->input[i][j] == '<')
					ms->token[i] = TOK_SINGLE_LEFT;
				else if (ms->input[i][j] == '>')
					ms->token[i] = TOK_SINGLE_RIGHT;
				else if (ms->input[i][j] == '$')
					ms->token[i] = TOK_DOLLAR;
				else if (ms->input[i][j] == '|')
					ms->token[i] = TOK_PIPE;
			}
			j++;
		}
		i++;
	}
}

char	**get_input(t_minishell *ms, char *cwd, char **envp)
{
	char	*line;

	line = readline(ft_strjoin(ft_strjoin
				("\033[38;5;39m[minishell] \033[4;36m", cwd),
				"\033[0;36m> \033[0m"));
	if (line == NULL)
		exit(0);
	ft_strtrim(line, " ");
	add_history(line);
	ms->input = lexer(line);
	get_token(ms);
	// remove_quotes(ms->input);
	check_dollar(ms->input, envp);
	return (ms->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	char		cwd[1024];

	ms = malloc(sizeof(t_minishell));
	if (!argv[0] || argc != 1)
		myexit(1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		getcwd(cwd, sizeof(cwd));
		ms->input = get_input(ms, cwd, envp);
		for (int i = 0; ms->input[i]; i++)
			printf("input[%d]: [%s] token:[%i]\n", i , ms->input[i], ms->token[i]);
		// cmd(ms->input, cwd, envp);
	}
}