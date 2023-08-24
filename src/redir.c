/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:00:37 by mliew             #+#    #+#             */
/*   Updated: 2023/07/12 20:00:37 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	rm_2strs(t_list *tmp, int i)
{
	free(tmp->args[i]);
	while (tmp->args[i])
	{
		tmp->args[i] = tmp->args[i + 2];
		i++;
	}
	return (0);
}

void	append_heredoc(t_list *tmp, int i, int tmpfd)
{
	if (!ft_strncmp(tmp->args[i], ">>\0", 3))
	{
		if (tmp->outfile)
			free(tmp->outfile);
		tmp->outfile = tmp->args[i + 1];
		tmp->append = 1;
		tmpfd = open(tmp->outfile, O_CREAT, 0644);
		close(tmpfd);
	}
	else if (!ft_strncmp(tmp->args[i], "<<\0", 3))
	{
		if (tmp->delimiter)
			free(tmp->delimiter);
		tmp->delimiter = tmp->args[i + 1];
	}
}

int	redir_type(t_list *tmp, int i)
{
	int	tmpfd;

	tmpfd = 0;
	if (!ft_strncmp(tmp->args[i], "<\0", 2))
	{
		if (tmp->infile)
			free(tmp->infile);
		tmp->infile = tmp->args[i + 1];
	}
	else if (!ft_strncmp(tmp->args[i], ">\0", 2))
	{
		if (tmp->outfile)
			free(tmp->outfile);
		tmp->outfile = tmp->args[i + 1];
		tmpfd = open(tmp->outfile, O_CREAT, 0644);
		close(tmpfd);
	}
	else if (!ft_strncmp(tmp->args[i], ">>\0", 3)
		||!ft_strncmp(tmp->args[i], "<<\0", 3))
		append_heredoc(tmp, i, tmpfd);
	else
		return (1);
	rm_2strs(tmp, i);
	return (0);
}

int	redir_error(t_minishell *ms, t_list *tmp, int i)
{
	if ((!ft_strncmp(tmp->args[i], "<\0", 2)
			|| !ft_strncmp(tmp->args[i], ">\0", 2)
			|| !ft_strncmp(tmp->args[i], ">>\0", 3)
			|| !ft_strncmp(tmp->args[i], "<<\0", 3))
		&& (!tmp->args[i + 1]
			|| !ft_strncmp(tmp->args[i + 1], "<\0", 2)
			|| !ft_strncmp(tmp->args[i + 1], ">\0", 2)
			|| !ft_strncmp(tmp->args[i + 1], ">>\0", 3)
			|| !ft_strncmp(tmp->args[i + 1], "<<\0", 3)))
	{
		printf("-minishell: syntax error\n");
		ms->exit_status = 2;
		return (1);
	}
	return (0);
}

int	redir(t_minishell *ms, t_list **lst)
{
	int		i;
	t_list	*tmp;

	tmp = *lst;
	while (tmp && tmp->args)
	{
		i = 0;
		while (tmp->args[i])
		{
			if (redir_error(ms, tmp, i) == 1)
				return (1);
			if (redir_type(tmp, i) == 1)
				i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
