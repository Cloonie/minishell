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

// void	check_valid_cmd(t_minishell *ms)
// {
// 	if (input[0])
// 	{
// 		if (ft_strncmp(input[0], "echo\0", 5) == 0
// 			|| ft_strncmp(input[0], "cd\0", 3) == 0
// 			|| ft_strncmp(input[0], "pwd\0", 4) == 0
// 			|| ft_strncmp(input[0], "export\0", 7) == 0
// 			|| ft_strncmp(input[0], "unset\0", 6) == 0
// 			|| ft_strncmp(input[0], "env\0", 4) == 0
// 			|| ft_strncmp(input[0], "exit\0", 5) == 0
// 			|| ft_strncmp(input[0], "./", 2) == 0
// 			|| ft_strncmp(input[0], "/", 1) == 0
// 			|| executable(input, envp))
// 	}
// }

int		is_executable(t_minishell *ms, int i)
{
	char	**paths;
	char	*current_path;
	int		j;

	(void)i;
	j = -1;
	paths = NULL;
	while (ms->envp[++j])
		if (ms->envp[j] && !ft_strncmp(ms->envp[j], "PATH=", 5))
			paths = ft_split(ft_strtrim(ms->envp[j], "PATH="), ':');
	j = -1;
	while (paths && paths[++j])
	{
		current_path = ft_strjoin(ft_strjoin(paths[j], "/"), ms->input[i]);
		if (access(current_path, F_OK) == 0)
		{
			ms->token[i] = TOK_CMD;
			return (0);
		}
	}
	return (1);
}

void	get_token(t_minishell *ms)
{
	int			i;
	// int			j;
	const char	*operators;

	operators = "\"\'><$|;\\";
	i = 0;
	ms->token = malloc(100);
	ms->infile = NULL;
	ms->outfile = NULL;
	while (ms->input[i] && ms->input[i][0])
	{
		if (ft_strchr(operators, ms->input[i][0]) != NULL)
		{
			if (ms->input[i][0] == '\"' || ms->input[i][0] == '\'')
				ms->token[i] = TOK_QUOTE;
			else if (ms->input[i][0] == '<')
			{
				ms->token[i] = TOK_REDIRECT;
				free(ms->infile);
				ms->infile = ft_strdup(ms->input[i + 1]);
			}
			else if (ms->input[i][0] == '>')
			{
				ms->token[i] = TOK_REDIRECT;
				free(ms->outfile);
				ms->outfile = ft_strdup(ms->input[i + 1]);
			}
			else if (ms->input[i][0] == '$')
				ms->token[i] = TOK_DOLLAR;
			else if (ms->input[i][0] == '|')
				ms->token[i] = TOK_PIPE;
		}
		else if ((ft_strncmp(ms->input[i], "echo\0", 5) == 0)
					|| (ft_strncmp(ms->input[i], "cd\0", 3) == 0)
					|| (ft_strncmp(ms->input[i], "pwd\0", 4) == 0)
					|| (ft_strncmp(ms->input[i], "export\0", 7) == 0)
					|| (ft_strncmp(ms->input[i], "unset\0", 6) == 0)
					|| (ft_strncmp(ms->input[i], "env\0", 4) == 0)
					|| (ft_strncmp(ms->input[i], "exit\0", 5) == 0))
			ms->token[i] = TOK_CMD;
		else if (is_executable(ms, i))
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
	ms->input = lexer(line);
	return (ms->input);
}

void	printlist(t_list *list)
{
	t_list *current;

	current = list;
	while (current != NULL)
	{
		printf("Command: %s\n", current->command);
		printf("Argument: %s\n", current->args);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	int			i;
	int			j;
	char		*args;
	t_list		**list;
	t_list		*temp;
	int			firstarg;

	ms = malloc(sizeof(t_minishell));
	ms->envp = envp;
	i = 0;
	firstarg = 1;
	*list = NULL;
	temp = NULL;
	if (!argv[0] || argc != 1)
		myexit(1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		getcwd(ms->cwd, sizeof(ms->cwd));
		ms->input = get_input(ms);
		get_token(ms);
		// check_spaces(ms);
		// remove_quotes(ms->input);
		// check_dollar(ms->input, ms->envp);
		for (int i = 0; ms->input[i]; i++)
			printf("input[%d]: [%s] token:[%i]\n", i , ms->input[i], ms->token[i]);
		printf("Infile is [%s]\n", ms->infile);
		printf("Outfile is [%s]\n", ms->outfile);
		while (ms->input[i] != NULL)
		{
			if (ms->token[i] == TOK_CMD)
			{
				j = i + 1;
				args = "";
				while (ms->input[j] != NULL && ms->token[j] == TOK_ARG)
				{
					if (firstarg)
					{
						args =  ft_strjoin(args, ms->input[j]);
						firstarg = 0;
					}
					else
						args = ft_strjoin(ft_strjoin(args, " "), ms->input[j]);
					j++;
				}
				temp = ft_lstnew(ms, ms->input[i], args);
				ft_lstadd_back(list, temp);
			}
			i++;
		}
		printlist(list);
	}
}
