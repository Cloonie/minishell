/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:52:11 by mliew             #+#    #+#             */
/*   Updated: 2023/05/07 15:52:11 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(char **input, char **envp)
{
	int	pipefd[2];
	int	child1;
	int	child2;

	if (pipe(pipefd) == -1)
		perror("pipe");
	child1 = fork();
	if (child1 == -1)
		perror("fork");
	if (child1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execlp("ls", "ls", NULL);
	}
	child2 = fork();
	if (child2 == -1)
		perror("fork");
	if (child2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("grep", "grep", "mini", NULL);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child2, NULL, 0);
	waitpid(child1, NULL, 0);
}
