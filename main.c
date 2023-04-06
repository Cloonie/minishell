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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <dirent.h>

#define Ctrl(x) ((x) & 0x1f)

void	ctrl_c(int sig)
{
	printf("\n"); // Print a newline to prompt for new input
	rl_on_new_line(); // Move cursor to the beginning of the line
	rl_replace_line("", 0); // Clear the current input line
	rl_redisplay(); // Redisplay the prompt
}

int	main(void)
{
	char	*input;
	char	cwd[1024];
	char	display[1024];
	DIR		*dir;
	struct dirent	*entry;

	signal(SIGINT, ctrl_c);
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
		if (strcmp(input, "ls") == 0)
		{
			dir = opendir(cwd);
			while ((entry = readdir(dir)) != NULL)
				printf("%s\n", entry->d_name);
			// closedir(dir);
		}
		add_history(input);
		free(input);
	}
	rl_clear_history();

	return (0);
}
