/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:36:38 by mliew             #+#    #+#             */
/*   Updated: 2023/08/23 18:37:05 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_dollar(t_minishell *ms)
{
	char	result[1024];
	char	temp[1024];
	int		i[3];

	i[0] = -1;
	while (ms->input[++i[0]])
	{
		i[1] = -1;
		ft_strlcpy(result, "", 1024);
		ms->quote = 0;
		while (ms->input[i[0]][++i[1]])
			check_dollar2(ms, temp, result, i);
		free(ms->input[i[0]]);
		ms->input[i[0]] = ft_strdup(result);
	}
}

void	check_dollar2(t_minishell *ms, char *temp, char *result, int i[3])
{
	ft_strlcpy(temp, "", 1024);
	i[2] = -1;
	if (ms->input[i[0]][i[1]] == '\'' && !ms->quote)
	{
		while (ms->input[i[0]][++i[1]] && ms->input[i[0]][i[1]] != '\'')
			temp[++i[2]] = ms->input[i[0]][i[1]];
		temp[++i[2]] = '\0';
		ft_strlcat(result, temp,
			ft_strlen(result) + ft_strlen(temp) + 1);
	}
	else if (ms->input[i[0]][i[1]] == '$'
		&& (ft_isalnum(ms->input[i[0]][i[1] + 1])
		|| ms->input[i[0]][i[1] + 1] == '?'))
		check_dollar3(ms, temp, result, i);
	else
		check_dollar4(ms, temp, result, i);
}

void	check_dollar3(t_minishell *ms, char *temp, char *result, int i[3])
{
	if (ms->input[i[0]][i[1] + 1] == '?')
		temp[++i[2]] = ms->input[i[0]][++i[1]];
	else
	{
		while (ms->input[i[0]][++i[1]] && ft_isalnum(ms->input[i[0]][i[1]]))
			temp[++i[2]] = ms->input[i[0]][i[1]];
		i[1]--;
	}
	temp[++i[2]] = '\0';
	if (ft_getenv(ms, temp))
		ft_strlcat(result, ft_getenv(ms, temp),
			ft_strlen(result) + ft_strlen(ft_getenv(ms, temp)) + 1);
}

void	check_dollar4(t_minishell *ms, char *temp, char *result, int i[3])
{
	if (ms->input[i[0]][i[1]] == '\"')
	{
		if (ms->quote == 0)
			ms->quote = 1;
		else
			ms->quote = 0;
	}
	else
	{
		temp[++i[2]] = ms->input[i[0]][i[1]];
		temp[++i[2]] = '\0';
		ft_strlcat(result, temp,
			ft_strlen(result) + ft_strlen(temp) + 1);
	}
}
