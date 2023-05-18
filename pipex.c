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

// int	main(void)
// {
// 	int	pipe_fd[2];
// 	int	pid;

// 	printf("Parent Process starts\n");
// 	if (pipe(pipe_fd) == -1)
// 		perror("pipe");
// 	pid = fork();
// 	if (pid == -1)
// 		perror("fork error");
// 	if (pid > 0)
// 		printf("Child Process starts\n");
// }

int main() {
    pid_t childPID;

    childPID = fork();

    if (childPID == -1) {
        printf("Fork failed!\n");
        return 1;
    }

    if (childPID == 0) {
        printf("Child process: PID=%d\n", getpid());
        // Child process code here
    } else {
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), childPID);
        // Parent process code here
    }

    return 0;
}