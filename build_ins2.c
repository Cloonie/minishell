/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:59:46 by mliew             #+#    #+#             */
/*   Updated: 2023/07/04 16:59:46 by mliew            ###   ########.fr       */
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
