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

char	**get_input(void)
{
	char	*input;
	char	**av;
	char	cwd[1024];

	input = readline(ft_strjoin(ft_strjoin("MK42@minishell:",
			getcwd(cwd, sizeof(cwd))), "> "));
	if (input == NULL)
		exit (0);
	ft_strtrim(input, " ");
	av = ft_split(input, ' ');
	add_history(input);
	return (av);
}

void	executable(char **input, char **ev)
{
	pid_t	pid;
	char	**paths;
	int		i;

	signal (SIGINT, ctrl);
	signal (SIGQUIT, SIG_IGN);
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	pid = fork();
	while (paths[i++])
	{
		if (pid == 0) // child process
			execve(ft_strjoin(ft_strjoin(paths[i], "/"), input[0]), input, ev);
		else if (pid > 0) // parent process
		{
			waitpid(pid, NULL, 0); // wait for child to finish
			break ;
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	char	**input;

	(void)ac;
	(void)av;
	(void)ev;

	signal(SIGINT, ctrl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = get_input();
		// executable(input, ev);
		// build_in(input, cwd, ev);
	}
	// free & exit
	rl_clear_history();
	free(input);
	return (0);
}
