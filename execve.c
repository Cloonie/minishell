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

void	executable(char **input, char **ev)
{
	pid_t	pid;
	char	**paths;
	int		i;

	signal (SIGINT, ctrl);
	signal (SIGQUIT, SIG_IGN);
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	pid = fork();
	while (paths[i++])
	{
		if (pid == 0) // child process
			execve(ft_strjoin(ft_strjoin(paths[i], "/"), input[0]), input, ev);
		else if (pid > 0) // parent process
		{
			waitpid(pid, NULL, 0); // wait for child to finish
			break ;
		}
	}
}
