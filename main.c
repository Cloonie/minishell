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

void	ctrl(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	**get_input(char *cwd)
{
	char	*input;
	char	**av;

	input = readline(ft_strjoin(ft_strjoin("MK42@minishell:", cwd), "> "));
	if (input == NULL)
		exit (0);
	ft_strtrim(input, " ");
	av = ft_split(input, ' ');
	add_history(input);
	return (av);
}

int	main(int ac, char **av, char **ev)
{
	char	**input;
	char	cwd[1024];

	(void)ac;
	(void)av;
	(void)ev;
	signal(SIGINT, ctrl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		getcwd(cwd, sizeof(cwd));
		input = get_input(cwd);
		build_in(input, cwd, ev);
	}
	rl_clear_history();
	free(input);
	return (0);
}
