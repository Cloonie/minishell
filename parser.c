/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:38:25 by mliew             #+#    #+#             */
/*   Updated: 2023/06/23 15:16:50 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_spaces(t_minishell *ms)
{
	int	i;
	int	ws;

	i = 0;
	while (ms->input[i] && ms->input[i + 1])
	{
		ws = ft_strlen(ms->input[i]) - 1;
		printf("[%c]\n", ms->input[i][ws]);
		if (ms->input[i][ws] != ' ')
			printf("No Space in between input.\n");
		ms->input[i] = ft_strtrim(ms->input[i], " ");
		i++;
	}
	ms->input[i] = ft_strtrim(ms->input[i], " ");
}

void	remove_quotes(char **array)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (array[i])
	{
		if (array[i][ft_strlen(array[i]) - 1] == ' ')
		{
			array[i] = ft_strtrim(array[i], " ");
			w = 1;
		}
		if (array[i][0] == '\"'
				&& array[i][ft_strlen(array[i]) - 1] == '\"')
			array[i] = ft_strtrim(array[i], "\"");
		else if (array[i][0] == '\''
				&& array[i][ft_strlen(array[i]) - 1] == '\'')
			array[i] = ft_strtrim(array[i], "\'");
		if (w == 1)
		{
			array[i][ft_strlen(array[i])] = ' ';
			array[i][ft_strlen(array[i]) + 1] = '\0';
			w = 0;
		}
		i++;
	}
}

char	**check_dollar(char **array, char **envp)
{
	int		i;
	int		j;
	char	*str;
	char	*var;

	i = -1;
	while (array[++i])
	{
		j = -1;
		var = ft_strtrim(&array[i][1], " ");
		while (array[i][0] == '$' && envp[++j] && array[i][1])
		{
			str = ft_substr(envp[j], 0, ft_strpos(envp[j], "="));
			if (ft_strncmp(str, var, ft_strlen(var) + 1) == 0)
				array[i] = ft_strchr(envp[j], '=') + 1;
			else if (!envp[j + 1])
				array[i] = "";
		}
	}
	return (array);
}
