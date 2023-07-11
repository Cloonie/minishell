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

void	rm_2strs(int i, char **array)
{
	while (array[i])
	{
		array[i] = array[i + 2];
		i++;
	}
}

void	redirection(t_minishell *ms, t_list **lst)
{
	int		i;
	t_list	*tmp;


	tmp = *lst;
	while (tmp && tmp->args)
	{
		i = 0;
		while (tmp->args[i])
		{
			if (!ft_strncmp(tmp->args[i], "<\0", 2))
			{
				ms->infile = tmp->args[i + 1];
				rm_2strs(i, tmp->args);
			}
			else if (!ft_strncmp(tmp->args[i], ">\0", 2))
			{
				ms->outfile = tmp->args[i + 1];
				rm_2strs(i, tmp->args);
			}
			else if (!ft_strncmp(tmp->args[i], ">>\0", 3))
			{
				ms->outfile = tmp->args[i + 1];
				rm_2strs(i, tmp->args);
			}
			else
				i++;
		}
		tmp = tmp->next;
	}
}

void	pipex(t_minishell *ms, t_list **lst)
{
	int	i;
	int	ret;
	int	fdpipe[2];
	int	size;

	size = ft_lstsize(*lst);
	ms->ori_in = dup(0);
	ms->ori_out = dup(1);
	if (ms->infile)
		ms->fdin = open(ms->infile, O_RDONLY);
	else
		ms->fdin = dup(ms->ori_in);

	i = -1;
	while (++i < size)
	{
		dup2(ms->fdin, 0);
		close(ms->fdin);
		if (i == size - 1)
		{
			if (ms->outfile)
				ms->fdout = open(ms->outfile,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				ms->fdout = dup(ms->ori_out);
		}
		else
		{
			pipe(fdpipe);
			ms->fdout = fdpipe[1];
			ms->fdin = fdpipe[0];
		}
		dup2(ms->fdout, 1);
		close(ms->fdout);
		ret = fork();
		if (ret == 0)
		{
			cmd(ms, lst);
			// perror("fork");
			exit(1);
		}
		if (ms->fdout != fdpipe[1])
			ms->outfile = NULL;
		(*lst) = (*lst)->next;
	}

	dup2(ms->ori_in, 0);
	dup2(ms->ori_out, 1);
	close(ms->ori_in);
	close(ms->ori_out);

	waitpid(ret, NULL, 0);
}
