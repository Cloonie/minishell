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

#include "minishell.h"

int	rm_2strs(t_list *tmp, int i)
{
	while (tmp->args[i])
	{
		tmp->args[i] = tmp->args[i + 2];
		i++;
	}
	return (0);
}

int	redir_type(t_list *tmp, int i)
{
	if (!ft_strncmp(tmp->args[i], "<\0", 2))
		tmp->infile = tmp->args[i + 1];
	else if (!ft_strncmp(tmp->args[i], ">\0", 2))
		tmp->outfile = tmp->args[i + 1];
	else if (!ft_strncmp(tmp->args[i], ">>\0", 3))
	{
		tmp->outfile = tmp->args[i + 1];
		tmp->append = 1;
	}
	else if (!ft_strncmp(tmp->args[i], "<<\0", 3))
	{
		tmp->outfile = "heredoc";
		// char *line;
		// line = readline(">");
		// printf("line: %s\n", line);
	}
	else
		return (1);
	rm_2strs(tmp, i);
	return (0);
}

int	redir_error(t_list *tmp, int i)
{
	if ((!ft_strncmp(tmp->args[i], "<\0", 2)
			|| !ft_strncmp(tmp->args[i], ">\0", 2)
			|| !ft_strncmp(tmp->args[i], ">>\0", 3)
			|| !ft_strncmp(tmp->args[i], "<<\0", 3))
		&& (tmp->args[i + 1] == NULL
			|| !ft_strncmp(tmp->args[i + 1], "<\0", 2)
			|| !ft_strncmp(tmp->args[i + 1], ">\0", 2)
			|| !ft_strncmp(tmp->args[i + 1], ">>\0", 3)
			|| !ft_strncmp(tmp->args[i + 1], "<<\0", 3)))
	{
		printf("-minishell: syntax error near unexpected token `%s'\n",
			tmp->args[i + 1]);
		return (1);
	}
	return (0);
}

int	redir(t_list **lst)
{
	int		i;
	t_list	*tmp;

	tmp = *lst;
	while (tmp && tmp->args)
	{
		i = 0;
		tmp->append = 0;
		tmp->infile = NULL;
		tmp->outfile = NULL;
		while (tmp->args[i])
		{
			if (redir_error(tmp, i) == 1)
				return (1);
			if (redir_type(tmp, i) == 1)
				i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
