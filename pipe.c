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

#include "minishell.h"

void	pipex(t_minishell *ms, t_list **lst)
{
	int		fdpipe[2];
	int		piped;

	ms->ori_in = dup(0);
	ms->ori_out = dup(1);
	ms->fdin = 0;
	ms->fdout = 0;
	piped = 0;

	while ((*lst))
	{
		if ((*lst)->delimiter)
		{
			int		tmp_fd;
			char	*input;
			ms->fdin = dup(ms->ori_in);
			ms->fdout = dup(ms->ori_out);
			dup2(ms->fdin, 0);
			dup2(ms->fdout, 1);
			close(ms->fdin);
			close(ms->fdout);
			tmp_fd = open("here_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
			input = readline("> ");
			while (input != NULL)
			{
				if ((!ft_strncmp(input, (*lst)->delimiter, ft_strlen((*lst)->delimiter) + 1)))
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
		else if ((*lst)->infile)
			ms->fdin = open((*lst)->infile, O_RDONLY);
		else if (piped)
			piped = 0;
		else
			ms->fdin = dup(ms->ori_in);
		if (ms->fdin == -1)
		{
			(*lst)->infile = NULL;
			perror("Error opening file");
			return ;
		}
		dup2(ms->fdin, 0);
		close(ms->fdin);

		pipe(fdpipe);
		if ((*lst)->outfile && !(*lst)->append)
			ms->fdout = open((*lst)->outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((*lst)->outfile && (*lst)->append)
			ms->fdout = open((*lst)->outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if ((*lst)->next)
		{
			ms->fdout = fdpipe[1];
			ms->fdin = fdpipe[0];
			piped = 1;
		}
		else
			ms->fdout = dup(ms->ori_out);
		dup2(ms->fdout, 1);
		close(ms->fdout);

		cmd(ms, lst);

		unlink("here_doc");
		if ((*lst)->next && !piped)
		{
			ms->fdout = fdpipe[1];
			dup2(ms->fdout, 1);
			close(ms->fdout);
			piped = 1;
		}
		(*lst) = (*lst)->next;
	}

	dup2(ms->ori_in, 0);
	dup2(ms->ori_out, 1);
	close(ms->ori_in);
	close(ms->ori_out);
}
