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

void	pipex(t_minishell *ms, t_list **lst)
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
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		cmd(ms, lst);
	}
	*lst = (*lst)->next;
	child2 = fork();
	if (child2 == -1)
		perror("fork");
	if (child2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		cmd(ms, lst);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child2, NULL, 0);
	waitpid(child1, NULL, 0);
	// pipex(ms, lst);
}

