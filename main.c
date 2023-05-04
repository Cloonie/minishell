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

char	*get_input(void)
{
	char	*input;
	char	cwd[1024];

	input = readline(ft_strjoin(ft_strjoin("MK42@minishell:",
			getcwd(cwd, sizeof(cwd))), "> "));
	ft_strtrim(input, " ");
	if (input == NULL)
		exit (0);
	add_history(input);
	return (input);
}

int	executable(char *input, char **ev)
{
	pid_t	pid;
	char	**av;
	char	**paths;
	int i = 0;

	signal (SIGINT, ctrl);
	signal (SIGQUIT, SIG_DFL);
	av = ft_split(input, ' ');
	paths = ft_split(getenv("PATH"), ':');
	while (i < 6)
	{
		pid = fork();
		if (pid == 0) // child process
		{
			execve(ft_strjoin(ft_strjoin(paths[i], "/"), av[0]), av, ev);
			// printf("Failed to execute command\n");
		} 
		else if (pid > 0) // parent process
		{
			waitpid(pid, NULL, 0); // wait for child to finish
			break ;
		}
		else // fork failed
			return 1;
		i++;
	}
	return 0;
}

int	main(int ac, char **av, char **ev)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)ev;

	signal(SIGINT, ctrl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = get_input();
		executable(input, ev);
	}
	// free & exit
	rl_clear_history();
	free(input);
	return (0);
}
