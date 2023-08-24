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

#include "../includes/minishell.h"

void	get_input(t_minishell *ms)
{
	char	*line;
	char	tmp[100];

	getcwd(ms->cwd, sizeof(ms->cwd));
	ft_strlcpy(tmp, "\033[38;5;39m[minishell] \033[4;36m", 30);
	ft_strlcat(tmp, ms->cwd, 100);
	ft_strlcat(tmp, "\033[0;36m> \033[0m", 100);
	line = readline(tmp);
	if (!line)
		exit(0);
	if (ft_strncmp(line, "", 1))
		add_history(line);
	ms->input = lexer(line, "<>|");
	if (!ms->exit_status)
		ms->exit_status = 0;
	free(line);
}

void	split_cmd(t_list **lst, t_minishell *ms)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tmp = malloc(sizeof(char *) * (MAX_BUF + 1));
	while (ms->input[++i])
	{
		if (!ft_strncmp(ms->input[i], "|\0", 2))
		{
			tmp[++j] = NULL;
			ft_lstadd_back(lst, ft_lstnew(tmp));
			tmp = malloc(sizeof(char *) * (MAX_BUF + 1));
			j = -1;
		}
		else
			tmp[++j] = ft_strdup(ms->input[i]);
	}
	tmp[++j] = NULL;
	ft_lstadd_back(lst, ft_lstnew(tmp));
}

void	init(t_minishell *ms, char **envp)
{
	ms->envp = envp;
	ms->quote = 0;
	tcgetattr(STDIN_FILENO, &ms->ori_attr);
	ms->new_attr = ms->ori_attr;
	ms->new_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCIFLUSH, &ms->new_attr);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;
	t_list		**lst;

	ms = malloc(sizeof(t_minishell));
	lst = malloc(sizeof(t_list));
	init(ms, envp);
	if (argv[1] || argc > 1)
		myexit(ms, lst, 1);
	while (1)
	{
		signal_handler(0);
		get_input(ms);
		if (!check_quotes(ms))
		{
			check_dollar(ms);
			check_emptystr(ms);
			split_cmd(lst, ms);
			tcsetattr(STDIN_FILENO, TCSANOW, &ms->ori_attr);
			if (!redir(ms, lst))
				final(ms, lst);
		}
		tcsetattr(STDIN_FILENO, TCIFLUSH, &ms->new_attr);
		ft_free(ms, lst);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &ms->ori_attr);
}
