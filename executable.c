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

int	cmd(t_minishell *ms, int i)
{ 
	if (ms->input[i])
	{
		if (ft_strncmp(ms->input[i], "echo\0", 5) == 0)
			call_echo(ms->input);
		else if (ft_strncmp(ms->input[i], "cd\0", 3) == 0)
			call_cd(ms->input, ms->cwd);
		else if (ft_strncmp(ms->input[i], "pwd\0", 4) == 0)
			printf("%s\n", ms->cwd);
		else if (ft_strncmp(ms->input[i], "export\0", 7) == 0)
			call_export(ms->input, ms->envp);
		else if (ft_strncmp(ms->input[i], "unset\0", 6) == 0)
			call_unset(ms->input, ms->envp);
		else if ((ft_strncmp(ms->input[i], "env\0", 4) == 0))
			call_env(ms->envp);
		else if (ft_strncmp(ms->input[i], "exit\0", 5) == 0)
			myexit(0);
		else if (ft_strncmp(ms->input[i], "./", 2) == 0
			|| ft_strncmp(ms->input[i], "/", 1) == 0)
			call_run(ms->input, ms->envp);
		else if (executable(ms->input, ms->envp, i))
		{
			printf("Enter a valid command.\n");
			return (1);
		}
	}
	return (0);
}

int	executable(char **input, char **envp, int j)
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
		current_path = ft_strjoin(ft_strjoin(paths[i], "/"), input[j]);
		// printf("(%s)\n", current_path);
		if (access(current_path, F_OK) == 0)
		{
			execve(current_path, input, envp);
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
	// perror("execve");
	return (1);
}

// int		executable(char **input, char **envp)
// {
// 	pid_t	pid;
// 	char	**paths;
// 	char	*current_path;
// 	int		i;

// 	input = ft_split(input[0], ' ');
// 	paths = ft_split(getenv("PATH"), ':');
// 	i = 0;
// 	while (paths[i] != NULL)
// 	{
// 		current_path = ft_strjoin(ft_strjoin(paths[i], "/"), input[0]);
// 		if (access(current_path, F_OK) == 0)
// 		{
// 			execve(current_path, input, envp);
// 			pid = fork();
// 			if (pid == 0)
// 				execve(current_path, input, envp);
// 			else if (pid > 0)
// 			{
// 				waitpid(pid, NULL, 0);
// 				break ;
// 			}
// 		}
// 		i++;
// 	}
// 	perror("execve");
// 	return (1);
// }

