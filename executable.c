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

void	executable(char **input, char **envp)
{
	pid_t	pid;
	char	**paths;
	char	*current_path;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i++])
	{
		current_path = ft_strjoin(ft_strjoin(paths[i], "/"), input[0]);
		if (access(current_path, F_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				// printf("%s\n", current_path);
				execve(current_path, input, envp);
			}
			else if (pid > 0)
			{
				waitpid(pid, NULL, 0);
				break ;
			}
		}
	}
}
