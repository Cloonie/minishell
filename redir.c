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
	if (tmp->args[i + 1] && tmp->args[i + 1][0]
			&& !ft_isalnum(tmp->args[i + 1][0]))
	{
		printf("-minishell: syntax error near unexpected token `%s'\n",
			tmp->args[i + 1]);
		return (1);
	}
	while (tmp->args[i])
	{
		tmp->args[i] = tmp->args[i + 2];
		i++;
	}
	return (0);
}

int	redir_type(t_minishell *ms, t_list *tmp, int i)
{
	if (!ft_strncmp(tmp->args[i], "<\0", 2))
		ms->infile = tmp->args[i + 1];
	else if (!ft_strncmp(tmp->args[i], ">\0", 2))
		ms->outfile = tmp->args[i + 1];
	else if (!ft_strncmp(tmp->args[i], ">>\0", 3))
	{
		ms->outfile = tmp->args[i + 1];
		ms->append = 1;
	}
	else
		return (2);
	if (rm_2strs(tmp, i) == 1)
		return (1);
	return (0);
}

int	redir(t_minishell *ms, t_list **lst)
{
	int		i;
	t_list	*tmp;

	tmp = *lst;
	ms->append = 0;
	while (tmp && tmp->args)
	{
		i = 0;
		while (tmp->args[i])
		{
			if (redir_type(ms, tmp, i) == 1)
				return (1);
			else
				i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
