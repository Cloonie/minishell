/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:25 by mliew             #+#    #+#             */
/*   Updated: 2023/06/28 00:14:22 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// closed: quoted = 0
// open: quoted = 1

int	check_quotes(t_minishell *ms)
{
	int	i;
	int	j;
	int	quoted;

	i = -1;
	quoted = 0;
	while (ms->input[++i])
	{
		j = -1;
		while (ms->input[i][++j])
		{
			if (ms->input[i][j] == '\'' || ms->input[i][j] == '\"')
			{
				if (quoted == 0)
					quoted = ms->input[i][j];
				else if (ms->input[i][j] == quoted)
					quoted = 0;
			}
		}
	}
	if(check_quotes2(ms, quoted) == 1)
		return (1);
	return (0);
}

int	check_quotes2(t_minishell *ms, int quoted)
{
	if (quoted != 0)
	{
		printf("Error quotes are not closed.\n");
		ms->exit_status = 130;
		return (1);
	}
	return (0);
}

void	check_emptystr(t_minishell *ms)
{
	int	i;

	i = -1;
	while (ms->input[++i])
	{
		if (!ft_strncmp(ms->input[i], "", ft_strlen(ms->input[i])))
		{
			free(ms->input[i]);
			while (ms->input[i])
			{
				ms->input[i] = ms->input[i + 1];
				i++;
			}
			i = -1;
		}
	}
}
