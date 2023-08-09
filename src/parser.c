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

void	check_dollar(t_minishell *ms)
{
	char	result[1024];
	char	temp[1024];
	int		i;
	int		j;
	int		k;
	int		quote;

	i = -1;
	while (ms->input[++i])
	{
		j = -1;
		ft_strlcpy(result, "", 1024);
		quote = 0;
		while (ms->input[i][++j])
		{
			ft_strlcpy(temp, "", 1024);
			k = -1;
			if (ms->input[i][j] == '\'' && !quote)
			{
				while (ms->input[i][++j] && ms->input[i][j] != '\'')
					temp[++k] = ms->input[i][j];
				temp[++k] = '\0';
				ft_strlcat(result, temp, ft_strlen(result) + ft_strlen(temp) + 1);
				// printf("temp: %s\n", temp);
			}
			else if (ms->input[i][j] == '$' && (ft_isalnum(ms->input[i][j + 1]) || ms->input[i][j + 1] == '?'))
			{
				if (ms->input[i][j + 1] == '?')
					temp[++k] = ms->input[i][++j];
				else
				{
					while (ms->input[i][++j] && ft_isalnum(ms->input[i][j]))
						temp[++k] = ms->input[i][j];
					j--;
				}
				temp[++k] = '\0';
				if (ft_getenv(ms, temp))
					ft_strlcat(result, ft_getenv(ms, temp), ft_strlen(result) + ft_strlen(ft_getenv(ms, temp)) + 1);
				// printf("temp: %s\n", temp);
			}
			else if (ms->input[i][j] == '\"')
			{
				if (quote == 0)
					quote = 1;
				else
					quote = 0;
			}
			else
			{
				temp[++k] = ms->input[i][j];
				temp[++k] = '\0';
				ft_strlcat(result, temp, ft_strlen(result) + ft_strlen(temp) + 1);
				// printf("temp: %s\n", temp);
			}
		}
		free(ms->input[i]);
		ms->input[i] = ft_strdup(result);
		// printf("result: %s\n", result);
	}
}
