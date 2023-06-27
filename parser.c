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

#include "minishell.h"

int	check_quotes(char *s)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	while (s[++i])
	{
		if (s[i] == '\"')
			d_quote++;
		if (s[i] == '\'')
			s_quote++;
	}
	if ((d_quote % 2) != 0 || (s_quote % 2) != 0)
	{
		printf("Error quotes are not closed.\n");
		return (1);
	}
	return (0);
}

void	remove_quotes(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i][0] == '\"'
				&& array[i][ft_strlen(array[i]) - 1] == '\"')
			array[i] = ft_strtrim(array[i], "\"");
		else if (array[i][0] == '\''
				&& array[i][ft_strlen(array[i]) - 1] == '\'')
			array[i] = ft_strtrim(array[i], "\'");
		i++;
	}
}

void	check_dollar(t_minishell *ms)
{
	char	**envvar;
	int		i;
	int		j;

	i = -1;
	while (ms->input[++i])
	{
		j = -1;
		if (ft_strchr(ms->input[i], '$'))
		{
			envvar = ft_split(ft_strchr(ms->input[i], '$') + 1, '$');
			ms->input[i] = ft_substr(ms->input[i], 0, ft_strpos(ms->input[i], "$"));
			while (envvar[++j])
			{
				if (ft_getenv(ms, envvar[j]))
					ms->input[i] = ft_strjoin(ms->input[i], ft_getenv(ms, envvar[j]));
				if (!ms->input[i])
					free(ms->input[i]);
				free(envvar[j]);
			}
			free(envvar);
		}
	}
}