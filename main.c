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

// int	count_strings(char **input)
// {
// 	static int	i;
// 	int			words;

// 	words = 0;
// 	while (!ft_strncmp(input[i], "|", 1))
// 		i++;
// 	while (input[i])
// 	{
// 		printf("input: %s\n", input[i]);
// 		if (!ft_strncmp(input[i], "|", 1))
// 			break ;
// 		words++;
// 		i++;
// 	}
// 	printf("words: %d\n", words);
// 	return (words);
// }

void	split_cmd(t_list **lst, char **input)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tmp = (char **)malloc(100);
	while (input[++i])
	{
		if (!ft_strncmp(input[i], "|", 1))
		{
			tmp[++j] = NULL;
			ft_lstadd_back(lst, ft_lstnew(tmp));
			tmp = (char **)malloc(100);
			j = -1;
		}
		else
			tmp[++j] = ft_strdup(input[i]);
	}
	tmp[++j] = NULL;
	ft_lstadd_back(lst, ft_lstnew(tmp));
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
		redirection(ms, lst);
		if (ft_strncmp((*lst)->args[0], "exit\0", 5) == 0)
			myexit(0);
		pipex(ms, lst);
		// while (*lst)
		// {
		// 	printf("NODE\n");
		// 	for (int x = 0; (*lst)->args[x]; x++)
		// 		printf("lst->args[%d]: %s\n", x, (*lst)->args[x]);
		// 	*lst = (*lst)->next;
		// }
		// for (int i = 0; ms->input[i]; i++)
		// 	printf("input[%d]: [%s] token:[%i]\n", i , ms->input[i], ms->token[i]);
		ft_free(ms, lst);
	}
}
