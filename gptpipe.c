#include "minishell.h"

int execute_command(char *command, char *input_file, char *output_file) {
	int input_fd, output_fd;

	// Open input file
	input_fd = open(input_file, O_RDONLY);
	if (input_fd == -1) {
		perror("open");
		return -1;
	}

	// Open output file
	output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1) {
		perror("open");
		return -1;
	}

	// Duplicate file descriptors for stdin and stdout
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);

	// Execute the command
	system(command);

	// Close file descriptors
	close(input_fd);
	close(output_fd);

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 5) {
		printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return 1;
	}

	char *file1 = argv[1];
	char *cmd1 = argv[2];
	char *cmd2 = argv[3];
	char *file2 = argv[4];

	int pipe_fd[2];
	if (pipe(pipe_fd) == -1) {
		perror("pipe");
		return 1;
	}

	pid_t pid1 = fork();
	if (pid1 == -1) {
		perror("fork");
		return 1;
	} else if (pid1 == 0) {
		// Child process 1
		close(pipe_fd[0]); // Close unused read end
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
		close(pipe_fd[1]); // Close pipe write end

		// Execute cmd1 with file1 as input
		execute_command(cmd1, file1, NULL);
		exit(0);
	}

	pid_t pid2 = fork();
	if (pid2 == -1) {
		perror("fork");
		return 1;
	} else if (pid2 == 0) {
		// Child process 2
		close(pipe_fd[1]); // Close unused write end
		dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe read end
		close(pipe_fd[0]); // Close pipe read end

		// Execute cmd2 with file2 as output
		execute_command(cmd2, NULL, file2);
		exit(0);
	}

	// Parent process
	close(pipe_fd[0]); // Close unused read end
	close(pipe_fd[1]); // Close unused write end

	// Wait for child processes to finish
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}