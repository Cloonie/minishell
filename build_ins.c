/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:23:16 by mliew             #+#    #+#             */
/*   Updated: 2023/04/09 15:23:16 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_exit(void)
{
	printf("Exit Minishell.\n");
	exit(0);
}

void	call_echo(char **input)
{
	int	i;
	int j;
	int p;
	int newline;

	i = 1;
	j = 1;
	p = 1;
	newline = 0;
	while (input[i] && input[i][j - 1] == '-')
	{
		while (input[i][j++] == 'n')
		{
			if (input[i][j] && input[i][j] != 'n')
				break;
			if (!input[i][j])
			{
				newline = 1;
				p++;
			}
		}
		i++;
		j = 1;
	}
	while (input[p])
	{
		printf("%s", input[p]);
		if (input[p + 1])
			printf(" ");
		p++;
	}
	if (!newline)
		printf("\n");
}

void	build_in(char **input, char *cwd, char **ev)
{
	// DIR				*dir;
	// struct dirent	*entry;
	int i;

	i = 0;
	if (strcmp(input[0], "echo") == 0)
		call_echo(input);
	if (strcmp(input[0], "cd") == 0)
		printf("cd\n");
	if (strcmp(input[0], "pwd") == 0)
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
	if (strcmp(input[0], "export") == 0)
		printf("export\n");
	if (strcmp(input[0], "unset") == 0)
		printf("unset\n");
	if ((strcmp(input[0], "env") == 0))
		while (ev[i])
			printf("%s\n", ev[i++]);
	if (strcmp(input[0], "exit") == 0)
		call_exit();

	// if (strcmp(input[0], "ls") == 0)
	// {
	// 	dir = opendir(cwd);
	// 	while ((entry = readdir(dir)) != NULL)
	// 		printf("%s\n", entry->d_name);
	// 	closedir(dir);
	// }
}
