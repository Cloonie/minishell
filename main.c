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

int	main(void)
{
	char	*input;
	char	cwd[1024];
	char	display[1024];
	// DIR		*dir;
	// struct dirent	*entry;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl);
	while (1)
	{
		getcwd(display, sizeof(cwd));
		getcwd(cwd, sizeof(cwd));
		strcat(display, "> ");
		input = readline(display);
		if (input == NULL)
		{
			printf("logout\n");
			break ;
		}
		if (strcmp(input, "pwd") == 0)
			printf("%s\n", cwd);
		// if (strcmp(input, "ls") == 0)
		// {
		// 	dir = opendir(cwd);
		// 	while ((entry = readdir(dir)) != NULL)
		// 		printf("%s\n", entry->d_name);
		// 	closedir(dir);
		// }

		pid_t pid;
		char *argv[] = {"/bin/cat", "makefile", NULL};
		char *envp[] = {NULL};

		pid = fork();

		if (pid == 0) { // child process
			execve(argv[0], argv, envp);
			printf("Failed to execute ls command\n");
		} else if (pid > 0) { // parent process
			wait(NULL); // wait for child to finish
			printf("Child process finished\n");
		} else { // fork failed
			printf("Failed to fork process\n");
			return 1;
		}

		add_history(input);
		free(input);
	}
	rl_clear_history();

	return (0);
}
