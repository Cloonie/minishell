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

// if quote = 0 means its close ""
// if quote = 1 means its open " and will look for the same type of quote

int	 check_quotes(t_minishell *ms)
{
	int	i;
	int	j;
	int	d_quote;
	int	s_quote;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	while (ms->input[++i])
	{
		j = -1;
		while (ms->input[i][++j])
		{
			if (ms->input[i][j] == '\"')
				d_quote++;
			else if (ms->input[i][j] == '\'')
				s_quote++;
		}
	}
	if ((d_quote % 2) != 0 || (s_quote % 2) != 0)
	{
		printf("Error quotes are not closed.\n");
		ms->exit_status = 130;
		return (1);
	}
	return (0);
}

void	remove_quotes(t_minishell *ms)
{
	char	*tmp;
	int		i;

	ms->token = malloc(MAX_BUF);
	i = -1;
	while (ms->input[++i])
	{
		ms->token[i] = 0;
		tmp = NULL;
		if (ms->input[i][0] == '\"'
				&& ms->input[i][ft_strlen(ms->input[i]) - 1] == '\"')
		{
			tmp = ft_strtrim(ms->input[i], "\"");
			ms->token[i] = 2;
		}
		else if (ms->input[i][0] == '\''
				&& ms->input[i][ft_strlen(ms->input[i]) - 1] == '\'')
		{
			tmp = ft_strtrim(ms->input[i], "\'");
			ms->token[i] = 1;
		}
		if (tmp)
		{
			free(ms->input[i]);
			ms->input[i] = tmp;
		}
	}
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

void	dollar_handler(t_minishell *ms, char **envvar, char	*res, int k)
{
	int		j;
	char	*tmp;
	char	*between;

	if (!ft_strncmp(envvar[k], "?", 1))
	{
		ft_strlcat(res, ft_itoa(ms->exit_status),
			ft_strlen(res) + ft_strlen(ft_itoa(ms->exit_status)) + 1);
		envvar[k] = ft_strchr(envvar[k], '?') + 1;
	}
	j = -1;
	while (ft_isalnum(envvar[k][++j]))
		;
	tmp = ft_substr(envvar[k], 0, j);
	if (ft_getenv(ms, tmp))
		ft_strlcat(res, ft_getenv(ms, tmp),
			ft_strlen(res) + ft_strlen(ft_getenv(ms, tmp)) + 1);
	free(tmp);
	between = ft_strchr(envvar[k], envvar[k][j]);
	if (between)
		ft_strlcat(res, between, ft_strlen(res) + ft_strlen(between) + 1);
}

void	multiple_dollar(t_minishell *ms, char **envvar, int i, int k)
{
	char	res[MAX_BUF];

	ft_strlcpy(res, ms->input[i], ft_strpos(ms->input[i], "$") + 1);
	k = -1;
	while (envvar[++k])
	{
		if (!ft_strncmp(envvar[k], "$", 1) && envvar[k + 1]
			&& envvar[k + 1][0] && ft_isalnum(envvar[k + 1][0]))
		{
			k++;
			dollar_handler(ms, envvar, res, k);
		}
		else
			ft_strlcat(res, envvar[k],
				ft_strlen(res) + ft_strlen(envvar[k]) + 1);
	}
	free(ms->input[i]);
	ms->input[i] = ft_strdup(res);
}

void	check_dollar(t_minishell *ms)
{
	char	**envvar;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	(void)j;
	while (ms->input[++i])
	{
		if (ft_strchr(ms->input[i], '$') && ms->token[i] != 1)
		{
			envvar = lexer(ft_strchr(ms->input[i], '$'), "$");
			for (int f = 0; envvar[f]; f++)
					printf("envvar[%d]: %s\n", f, envvar[f]);
			multiple_dollar(ms, envvar, i, k);
			k = -1;
			while (envvar[++k])
				free(envvar[k]);
			free(envvar);
		}
	}
}
