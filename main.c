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

	input = readline(ft_strjoin(ft_strjoin("MK42@minishell", getcwd(cwd, sizeof(cwd))), "> "));
	ft_strtrim(input, " ");
	if (input == NULL)
		exit (0);
	add_history(input);
	return (input);
}

int	executable(char *input, char **ev)
{
	pid_t pid;
	char **array;

	array = ft_split(input, ' ');
	array[0] = ft_strjoin("/bin/", array[0]);
	pid = fork();
	if (pid == 0)
	{	// child process
		execve(bin[0], bin, ev);
		printf("Failed to execute bin command\n");
	} 
	else if (pid > 0)
	{	// parent process
		wait(NULL); // wait for child to finish
		// printf("Child process finished\n");
	}
	else 
	{	// fork failed
		printf("Failed to fork process\n");
		return 1;
	}
	return 0;
}

int	main(int ac, char **av, char **ev)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)ev;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl);
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
