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

#include <stdio.h>
#include <unistd.h>

int create_pipe(int *fd) {
    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe");
        return -1;
    }
    return 0;
}

int main() {
    int fd[2];
    char buffer[10];

    if (create_pipe(fd) == -1) {
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(fd[1]); // Close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child: Received message: %s\n", buffer);
        close(fd[0]);
    } else {
        // Parent process
        close(fd[0]); // Close read end
        write(fd[1], "Hello", 6);
        printf("Parent: Sent message: Hello\n");
        close(fd[1]);
    }

    return 0;
}