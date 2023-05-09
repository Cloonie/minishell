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

void	call_echo(char **input)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 1;
	newline = 0;
	if (input[i] && input[i][j - 1] == '-' && input[i][j] == 'n')
	{
		newline = 1;
		i++;
	}
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1])
			printf(" ");
		i++;
	}
	if (!newline)
		printf("\n");
}

void	call_unset(char **input)
{
	char	*to_unset;

	to_unset = NULL;
	if (input[1])
	{
		to_unset = getenv(input[1]);
		printf("%s\n", to_unset);
		unsetenv(to_unset);
		printf("%s\n", to_unset);
	}
}

void	call_cd(char **input, char *cwd)
{
	char	*path;

	if (input[1] && input[1][0] == '/')
	{
		if (chdir(input[1]) == 0)
			;
		else
			printf("%s: %s: No such file or directory\n", input[0], input[1]);
	}
	else if (input[1])
	{
		path = ft_strjoin(ft_strjoin(cwd, "/"), input[1]);
		if (chdir(path) == 0)
			;
		else
			printf("%s: %s: No such file or directory\n", input[0], input[1]);
	}
	else
		chdir(getenv("HOME"));
}

void	build_in(char **input, char *cwd, char **ev)
{
	int	i;

	i = 0;
	if (input[0])
	{
		if (strcmp(input[0], "echo") == 0)
			call_echo(input);
		else if (strcmp(input[0], "cd") == 0)
			call_cd(input, cwd);
		else if (strcmp(input[0], "pwd") == 0)
			printf("%s\n", cwd);
		// else if (strcmp(input[0], "export") == 0)
		// 	printf("export\n");
		else if (strcmp(input[0], "unset") == 0)
			call_unset(input);
		else if ((strcmp(input[0], "env") == 0))
			while (ev[i])
				printf("%s\n", ev[i++]);
		else if (strcmp(input[0], "exit") == 0)
		{
			printf("Exit Minishell.\n");
			exit(0);
		}
		else
			executable(input, ev);
	}
}

// void	call_ls(void)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	if (strcmp(input[0], "ls") == 0)
// 	{
// 		dir = opendir(cwd);
// 		while ((entry = readdir(dir)) != NULL)
// 			printf("%s\n", entry->d_name);
// 		closedir(dir);
// 	}
// }
