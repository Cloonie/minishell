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
}

void	cmd(char **input, char *cwd, char **envp)
{
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
		else if (ft_strncmp(input[0], "unset", 5) == 0)
			call_unset(input, envp);
		else if ((ft_strncmp(input[0], "env", 3) == 0))
			call_env(envp);
		else if (ft_strncmp(input[0], "exit", 4) == 0)
			myexit(0);
		else if (ft_strncmp(input[0], "./", 2) == 0)
			call_run(input, envp);
		else
			executable(input, envp);
	}
}

void	executable(char **input, char **envp)
{
	pid_t	pid;
	char	**paths;
	char	*current_path;
	int		i;

	input = ft_split(input[0], ' ');
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i] != NULL)
	{
		current_path = ft_strjoin(ft_strjoin(paths[i], "/"), input[0]);
		if (access(current_path, F_OK) == 0)
		{
			execve(current_path, input, envp);
			pid = fork();
			if (pid == 0)
				execve(current_path, input, envp);
			else if (pid > 0)
			{
				waitpid(pid, NULL, 0);
				break ;
			}
		}
		i++;
	}
	perror("execve");
}
