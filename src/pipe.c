/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:44:31 by mliew             #+#    #+#             */
/*   Updated: 2023/07/11 22:44:31 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	stdio_readline(t_minishell *ms)
{
	ms->fdin = dup(ms->ori_in);
	dup2(ms->fdin, 0);
	close(ms->fdin);
	ms->fdout = dup(ms->ori_out);
	dup2(ms->fdout, 1);
	close(ms->fdout);
}

void	here_doc(t_minishell *ms, t_list **lst)
{
	int		tmp_fd;
	char	*input;

	stdio_readline(ms);
	tmp_fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	input = readline("> ");
	while (input != NULL)
	{

		if ((!ft_strncmp(input, (*lst)->delimiter,
					ft_strlen((*lst)->delimiter) + 1)
				|| !ft_strncmp(input, "^C", 2)))
		{
			free(input);
			break ;
		}
		write(tmp_fd, input, ft_strlen(input));
		write(tmp_fd, "\n", 1);
		free(input);
		input = readline("> ");
	}
	close(tmp_fd);
	ms->fdin = open("here_doc", O_RDONLY);
}
int	input(t_minishell *ms, t_list **lst)
{
	if ((*lst)->delimiter)
		here_doc(ms, lst);
	else if ((*lst)->infile)
		ms->fdin = open((*lst)->infile, O_RDONLY);
	else if ((*lst)->fdpipe[0] != -1 && (*lst)->fdpipe[0] != 0)
	{
		ms->fdin = (*lst)->fdpipe[0];
		// printf("%s, c pipe in: %d\n", (*lst)->args[0], ms->fdin);
	}
	else
	{
		// printf("STDIN\n");
		ms->fdin = dup(ms->ori_in);
	}
	if (ms->fdin == -1)
	{
		perror("fdin is -1");
		(*lst)->infile = NULL;
		return (1);
	}
	// printf("ms->fdin: %d\n", ms->fdin);
	if (dup2(ms->fdin, 0) == -1)
	{
		perror("dup2 fdin");
		return (1);
	}
	close(ms->fdin);
	return (0);
}

void	output(t_minishell *ms, t_list **lst)
{
	if ((*lst)->outfile && !(*lst)->append)
			ms->fdout = open((*lst)->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*lst)->outfile && (*lst)->append)
		ms->fdout = open((*lst)->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if ((*lst)->next)
	{
		ms->fdout = (*lst)->next->fdpipe[1];
		// close((*lst)->next->fdpipe[0]);
		// printf("%s, c pipe out: %d\n", (*lst)->args[0], ms->fdout);
	}
	else
	{
		// printf("STDOUT\n");
		ms->fdout = dup(ms->ori_out);
	}
	// printf("ms->fdout: %d\n", ms->fdout);
	if (dup2(ms->fdout, 1) == -1)
	{
		perror("dup2 fdout");
		return ;
	}
	close(ms->fdout);
}

void	pipex(t_minishell *ms, t_list **lst)
{
	t_list	*head;
	pid_t	*child;
	int		i;

	i = -1;
	head = *lst;
	child = malloc(sizeof(pid_t) * ft_lstsize(*lst));
	init_pipe(ms);
	while ((*lst))
	{
		if ((*lst)->next)
			pipe((*lst)->next->fdpipe);
		input(ms, lst);
		output(ms, lst);
		child[++i] = fork();
		if (child[i] == 0)
		{
			// printf("\nchild: %d\n", i);
			// printf("c fdpipe[0]: %d\n", (*lst)->fdpipe[0]);
			// printf("c fdpipe[1]: %d\n", (*lst)->fdpipe[1]);
			if (!ft_strncmp((*lst)->args[0], "cat", 3))
				close((*lst)->next->fdpipe[0]);
			cmd(ms, lst);
			exit(0);
		}
		run_build_ins(ms, lst);
		if ((*lst)->next)
			close((*lst)->next->fdpipe[1]);
		close((*lst)->fdpipe[0]);
		unlink("here_doc");
		(*lst) = (*lst)->next;
	}
	i = -1;
	while (child[++i])
		waitpid(child[i], NULL, 0);
	free(child);
	dup2(ms->ori_in, 0);
	dup2(ms->ori_out, 1);
	close(ms->ori_in);
	close(ms->ori_out);
	*lst = head;
}
