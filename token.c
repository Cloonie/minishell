/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:56:41 by mliew             #+#    #+#             */
/*   Updated: 2023/07/04 16:56:41 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_cmd(t_minishell *ms, char *input)
{
	char	**path;
	int		i;

	i = -1;
	if (input && (ft_strncmp(input, "echo\0", 5) == 0
			|| ft_strncmp(input, "cd\0", 3) == 0
			|| ft_strncmp(input, "pwd\0", 4) == 0
			|| ft_strncmp(input, "export\0", 7) == 0
			|| ft_strncmp(input, "unset\0", 6) == 0
			|| ft_strncmp(input, "env\0", 4) == 0
			|| ft_strncmp(input, "exit\0", 5) == 0
			|| ft_strncmp(input, "./", 2) == 0
			|| ft_strncmp(input, "/", 1) == 0))
		return (1);
	else if (input && ft_getenv(ms, "PATH"))
	{
		path = ft_split(ft_getenv(ms, "PATH"), ':');
		while (path[++i])
			if (access(ft_strjoin(ft_strjoin(path[i], "/"), input), F_OK) == 0)
				return (1);
	}
	return (0);
}

void	get_token(t_minishell *ms)
{
	int			i;
	int			j;
	const char	*operators;

	operators = "\"\'><$|;\\";
	i = 0;
	j = 0;
	ms->token = malloc(100);
	while (ms->input[i] && ms->input[i][0])
	{
		if (ft_strchr(operators, ms->input[i][0]) != NULL)
		{
			if (ms->input[i][0] == '\"')
				ms->token[i] = TOK_DQUOTE;
			else if (ms->input[i][0] == '\'')
				ms->token[i] = TOK_SQUOTE;
			else if (ms->input[i][0] == '<' || ms->input[i][0] == '>')
				ms->token[i] = TOK_REDIRECT;
			else if (ms->input[i][0] == '$')
				ms->token[i] = TOK_DOLLAR;
			else if (ms->input[i][0] == '|')
				ms->token[i] = TOK_PIPE;
			j = 0;
		}
		else if (check_valid_cmd(ms, ms->input[i]) && j == 0)
		{
			ms->token[i] = TOK_CMD;
			j = 1;
		}
		else
			ms->token[i] = TOK_ARG;
		i++;
	}
}
