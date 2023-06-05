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

int	main(void)
{
	int	forkpid;

	forkpid = fork();
	if (forkpid == -1)
		perror("fork");
	if (forkpid == 0)
	{
		printf("this is child process, forkpid: %d\n", forkpid);
		printf("childpid: %d\n", getpid());
	}
	else if (forkpid > 0)
	{
		waitpid(forkpid, NULL, 0);
		printf("this is parent process, forkpid: %d\n", forkpid);
		printf("parentpid: %d\n", getpid());
	}
}
