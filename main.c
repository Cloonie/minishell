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
		printf("\n"); // Print a newline to prompt for new input
		rl_on_new_line(); // Move cursor to the beginning of the line
		rl_replace_line("", 0); // Clear the current input line
		rl_redisplay(); // Redisplay the prompt
	}
}

char	**get_input(char *cwd)
{
	char	*input;
	char	**av;

	input = readline(ft_strjoin(ft_strjoin("MK42@minishell:",
			cwd), "> "));
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
	getcwd(cwd, sizeof(cwd));
	while (1)
	{
		input = get_input(cwd);
		// executable(input, ev);
		build_in(input, cwd, ev);
	}
	// free & exit
	rl_clear_history();
	free(input);
	return (0);
}
