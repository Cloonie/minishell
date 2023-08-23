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
	tmp_fd = open(".tmp", O_WRONLY | O_CREAT, 0644);
	input = readline("> ");
	while (input != NULL)
	{
		if ((!ft_strncmp(input, (*lst)->delimiter,
					ft_strlen((*lst)->delimiter) + 1)))
		{
			free(input);
			break ;
		}
		write(tmp_fd, input, ft_strlen(input));
		write(tmp_fd, "\n", 1);
		free(input);
		input = readline("> ");
		signal_handler(1);
	}
	close(tmp_fd);
}

int	input(t_minishell *ms, t_list **lst)
{
	if ((*lst)->delimiter && (*lst)->flag == 1)
		ms->fdin = open(".tmp", O_RDONLY);
	else if ((*lst)->infile)
		ms->fdin = open((*lst)->infile, O_RDONLY);
	else if ((*lst)->fdpipe[0] != -1 && (*lst)->fdpipe[0] != 0)
		ms->fdin = (*lst)->fdpipe[0];
	else
		ms->fdin = dup(ms->ori_in);
	if (ms->fdin == -1)
	{
		perror("fdin is -1");
		(*lst)->infile = NULL;
		return (1);
	}
	if (dup2(ms->fdin, 0) == -1)
	{
		perror("dup2 fdout");
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
		close((*lst)->next->fdpipe[0]);
	}
	else
		ms->fdout = dup(ms->ori_out);
	if (dup2(ms->fdout, 1) == -1)
	{
		perror("dup2 fdout");
		return ;
	}
	close(ms->fdout);
}
