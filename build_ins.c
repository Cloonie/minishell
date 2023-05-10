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

void	call_unset(char **input, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], ft_strchr(input[1], '='), ft_strlen(input[1])))
		{
			envp[i] = NULL;
			i = j;
			while (envp[++j])
			{
				envp = envp[j + 1];
			}
		}
		i++;
	}
}

void	call_export(char **input, char **envp)
{
	int	i;

	i = 0;
	if (!input[1])
		return ;
	while (envp[i])
	{
		if (!envp[i + 1])
		{
			envp[i + 1] = input[1];
			envp[i + 2] = NULL;
			break ;
		}
		i++;
	}
}

void	build_in(char **input, char *cwd, char **envp)
{
	int	i;

	i = 0;
	if (input[0])
	{
		if (ft_strncmp(input[0], "echo", 4) == 0)
			call_echo(input);
		else if (ft_strncmp(input[0], "cd", 2) == 0)
			call_cd(input, cwd);
		else if (ft_strncmp(input[0], "pwd", 3) == 0)
			printf("%s\n", cwd);
		else if (ft_strncmp(input[0], "export", 6) == 0)
			call_export(input, envp);
		// else if (ft_strncmp(input[0], "unset", 5) == 0)
		// 	call_unset(input, envp);
		else if ((ft_strncmp(input[0], "env", 3) == 0))
			while (envp[i])
				printf("%s\n", envp[i++]);
		else if (ft_strncmp(input[0], "exit", 4) == 0)
		{
			printf("Exit Minishell.\n");
			exit(0);
		}
		else
			executable(input, envp);
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
