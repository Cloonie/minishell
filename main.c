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

char	**get_input(t_minishell *ms)
{
	char	*line;

	line = readline(ft_strjoin(ft_strjoin
				("\033[38;5;39m[minishell] \033[4;36m", ms->cwd),
				"\033[0;36m> \033[0m"));
	if (line == NULL)
		exit(0);
	ft_strtrim(line, " ");
	add_history(line);
	ms->input = lexer(line, " ><|");
	return (ms->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	ms->envp = envp;
	if (!argv[0] || argc != 1)
		myexit(1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		getcwd(ms->cwd, sizeof(ms->cwd));
		ms->input = get_input(ms);
		get_token(ms);
		remove_quotes(ms->input);
		check_dollar(ms);
		check_emptystr(ms);
		cmd(ms);
		for (int i = 0; ms->input[i]; i++)
			printf("input[%d]: [%s] token:[%i]\n", i , ms->input[i], ms->token[i]);
	}
}
