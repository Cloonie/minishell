/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:51:54 by mliew             #+#    #+#             */
/*   Updated: 2023/05/07 15:51:54 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i++]);
		else
			i++;
	}
}

void	call_run(char **input, char **envp)
{
	int		pid;

	if (access(input[0], F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(input[0], input, envp);
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
			return ;
		}
	}
	else
		printf("Enter a valid command.\n");
}

int	cmd(char **input, char *cwd, char **envp)
{
	if (input[0])
	{
		if (ft_strncmp(input[0], "echo\0", 5) == 0)
			call_echo(input);
		else if (ft_strncmp(input[0], "cd\0", 3) == 0)
			call_cd(input, cwd);
		else if (ft_strncmp(input[0], "pwd\0", 4) == 0)
			printf("%s\n", cwd);
		else if (ft_strncmp(input[0], "export\0", 7) == 0)
			call_export(input, envp);
		else if (ft_strncmp(input[0], "unset\0", 6) == 0)
			call_unset(input, envp);
		else if ((ft_strncmp(input[0], "env\0", 4) == 0))
			call_env(envp);
		else if (ft_strncmp(input[0], "exit\0", 5) == 0)
			myexit(0);
		else if (ft_strncmp(input[0], "./", 2) == 0
			|| ft_strncmp(input[0], "/", 1) == 0)
			call_run(input, envp);
		else if (executable(input, envp))
		{
			printf("Enter a valid command.\n");
			return (1);
		}
	}
	return (0);
}

int	executable(char **input, char **envp)
{
	pid_t	pid;
	char	**paths;
	char	*current_path;
	int		i;

	i = -1;
	paths = NULL;
	while (envp[++i])
		if (envp[i] && !ft_strncmp(envp[i], "PATH=", 5))
			paths = ft_split(ft_strtrim(envp[i], "PATH="), ':');
	i = -1;
	while (paths && paths[++i])
	{
		current_path = ft_strjoin(ft_strjoin(paths[i], "/"), input[0]);
		if (access(current_path, F_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve(current_path, input, envp);
			else if (pid > 0)
			{
				waitpid(pid, NULL, 0);
				return (0);
			}
		}
	}
	return (1);
}
