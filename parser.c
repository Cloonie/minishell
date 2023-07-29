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

void	remove_quotes(t_minishell *ms)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ms->input[i])
	{
		tmp = NULL;
		if (ms->input[i][0] == '\"'
				&& ms->input[i][ft_strlen(ms->input[i]) - 1] == '\"')
			tmp = ft_strtrim(ms->input[i], "\"");
		else if (ms->input[i][0] == '\''
				&& ms->input[i][ft_strlen(ms->input[i]) - 1] == '\'')
			tmp = ft_strtrim(ms->input[i], "\'");
		if (tmp)
		{
			free(ms->input[i]);
			ms->input[i] = tmp;
		}
		i++;
	}
}

void	check_emptystr(t_minishell *ms)
{
	int	i;
	int	j;

	i = -1;
	while (ms->input[++i])
	{
		j = i - 1;
		if (j >= 0 && !ft_strncmp(ms->input[i], "", ft_strlen(ms->input[i])))
		{
			free(ms->input[j]);
			while (ms->input[++j])
				ms->input[j] = ms->input[j + 1];
		}
	}
}

void	multiple_dollar(t_minishell *ms, int i, int j)
{
	int		k;
	char	**envvar;
	char	*between;
	char	tmp[100];

	envvar = ft_split(ft_strchr(ms->input[i], '$'), '$');
	// for (int f = 0; envvar[f]; f++)
	// 	printf("envvar[%d]: %s\n", f, envvar[f]);
	ft_strlcpy(tmp, ft_substr(ms->input[i], 0, ft_strpos(ms->input[i], "$")), 100);
	k = -1;
	while (envvar[++k])
	{
		j = -1;
		if (!ft_strncmp(envvar[k], "?", 1))
		{
			ft_strlcat(tmp, ft_itoa(ms->exit_status), 100);
			envvar[k] = ft_strchr(envvar[k], '?') + 1;
		}
		while (ft_isalnum(envvar[k][++j]))
			;
		between = ft_strchr(envvar[k], envvar[k][j]);
		envvar[k] = ft_substr(envvar[k], 0, j);
		if (ft_getenv(ms, envvar[k]))
			ft_strlcat(tmp, ft_getenv(ms, envvar[k]), 100);
		if (between)
			ft_strlcat(tmp, between, 100);
		// printf("input[%d]: |%s|\n", i, ms->input[i]);
		// printf("between: %s\n", between);
	}
	ft_strlcpy(ms->input[i], tmp, ft_strlen(tmp) + 1);
}

void	check_dollar(t_minishell *ms)
{
	int		i;
	int		j;

	i = -1;
	while (ms->input[++i])
	{
		j = -1;
		while (ms->input[i][++j])
		{
			if (ms->input[i][j] && ms->input[i][j] == '$')
				;
			else if (ft_strchr(ms->input[i], '$') && ms->token[i] != TOK_SQUOTE)
				multiple_dollar(ms, i, j);
			// else if (!ft_strncmp(ms->input[i], "$?\0", 3)
			// 	&& ms->token[i] != TOK_SQUOTE)
			// {
			// 	free(ms->input[i]);
			// 	ms->input[i] = ft_itoa(ms->exit_status);
			// }
		}
	}
}
