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

int	get_mallocsize(char **input)
{
	static int	i;
	static int	previous;

	previous = i;
	while (input[i] != NULL)
	{
		if (ft_strncmp(input[0], "|", 1) == 0)
			break;
		else
			i++;
	}
	printf("i: %d | previous: %d\n", i, previous);
	return (i - previous);
}

void	split_cmd(t_list **lst, char **input)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	printf("malloc: %d\n", get_mallocsize(input));
	tmp = malloc(100);
	while (input[++i])
	{
		if (!ft_strncmp(input[i], "|", 1))
		{
			tmp[++j] = NULL;
			ft_lstadd_back(lst, ft_lstnew(tmp));
			tmp = malloc(100);
			j = -1;
		}
		else
			tmp[++j] = ft_strdup(input[i]);
	}
	tmp[++j] = NULL;
	ft_lstadd_back(lst, ft_lstnew(tmp));
	while (*lst)
	{
		printf("NODE\n");
		for (int x = 0; (*lst)->cmd[x]; x++)
			printf("lst->cmd[%d]: %s\n", x, (*lst)->cmd[x]);
		*lst = (*lst)->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	t_list		**lst;

	ms = malloc(sizeof(t_minishell));
	lst = malloc(sizeof(t_list));
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
		split_cmd(lst, ms->input);
		cmd(ms);
		// for (int i = 0; ms->input[i]; i++)
		// 	printf("input[%d]: [%s] token:[%i]\n", i , ms->input[i], ms->token[i]);
	}
}
