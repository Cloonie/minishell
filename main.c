/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 00:07:08 by mliew             #+#    #+#             */
/*   Updated: 2023/04/04 00:07:08 by mliew            ###   ########.fr       */
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
	const char	*operators;

	operators = "\"\'><$|;\\";
	i = 0;
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
		}
		else if (check_valid_cmd(ms, ms->input[i]))
			ms->token[i] = TOK_CMD;
		else
			ms->token[i] = TOK_ARG;
		i++;
	}
}

char	**get_input(t_minishell *ms)
{
	char	*line;

	line = readline(ft_strjoin(ft_strjoin
				("\033[38;5;39m[minishell] \033[4;36m", ms->cwd),
				"\033[0;36m> \033[0m"));
	if (line == NULL)
		exit(0);
	ft_strtrim(line, " ");
	add_history(line);
	ms->input = lexer(line, " ><|");
	return (ms->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	ms->envp = envp;
	if (!argv[0] || argc != 1)
		myexit(1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		getcwd(ms->cwd, sizeof(ms->cwd));
		ms->input = get_input(ms);
		get_token(ms);
		remove_quotes(ms->input);
		check_dollar(ms);
		check_emptystr(ms);
		cmd(ms);
		for (int i = 0; ms->input[i]; i++)
			printf("input[%d]: [%s] token:[%i]\n", i , ms->input[i], ms->token[i]);
	}
}
