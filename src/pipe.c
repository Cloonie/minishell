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

int	input(t_minishell *ms, t_list **lst, int *fdpipe)
{
	printf("INPUT!\n");
	printf("start of in prevread: %d\n", (*lst)->prev_read);
	(void)fdpipe;
	if ((*lst)->delimiter)
		here_doc(ms, lst);
	else if ((*lst)->infile)
		ms->fdin = open((*lst)->infile, O_RDONLY);
	else if ((*lst)->prev_read)
	{
		ms->fdin = (*lst)->prev_read;
		printf("input prevread: %d\n", (*lst)->prev_read);
	}
	else
		ms->fdin = dup(ms->ori_in);
	if (ms->fdin == -1)
	{
		perror((*lst)->infile);
		(*lst)->infile = NULL;
		return (1);
	}
	dup2(ms->fdin, 0);
	close(ms->fdin);
	return (0);
}

void	output(t_minishell *ms, t_list **lst, int *fdpipe)
{
	printf("OUTPUT!\n");
	if ((*lst)->outfile && !(*lst)->append)
			ms->fdout = open((*lst)->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*lst)->outfile && (*lst)->append)
		ms->fdout = open((*lst)->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if ((*lst)->next)
	{
		ms->fdout = fdpipe[1];
		(*lst)->next->prev_read = fdpipe[0];
		close(fdpipe[0]);
		printf("output prevread: %d\n", (*lst)->next->prev_read);
	}
	else
		ms->fdout = dup(ms->ori_out);
	dup2(ms->fdout, 1);
	close(ms->fdout);
}

void	repipe(t_minishell *ms, int *fdpipe)
{
	ms->fdout = fdpipe[1];
	dup2(ms->fdout, 1);
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
		child[++i] = fork();
		if (child[i] == 0)
		{
			pipe((*lst)->fdpipe);
			if (input(ms, lst, (*lst)->fdpipe) == 1)
				return ;
			output(ms, lst, (*lst)->fdpipe);
			cmd(ms, lst);
			unlink("here_doc");
			// repipe(ms, (*lst)->fdpipe);
			printf("\n");
			exit(0);
		}
		(*lst) = (*lst)->next;
	}
	i = -1;
	while (child[++i])
		waitpid(child[i], NULL, 0);
	dup2(ms->ori_in, 0);
	dup2(ms->ori_out, 1);
	close(ms->ori_in);
	close(ms->ori_out);
	*lst = head;
}
