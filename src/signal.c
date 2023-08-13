/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:33:08 by kcheong           #+#    #+#             */
/*   Updated: 2023/08/09 11:33:08 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_slash(int sig)
{
	(void)sig;
	printf("\b\b\bQuit (core dumped)\n");	
}

void	ctrl_c_heredoc(int sig)
{
	(void)sig;
	g_quit_heredoc = 1;
	// kill(0, SIGUSR1);
}

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\b \b");
	printf("\b \b");
	printf("\n");
}

void	new_prompt(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	signal_handler(int sig, int pid)
{
	// (void)ms;
	(void)pid;
	if (sig == 1)
	{
		// printf("1\n");
		signal(SIGINT, new_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		// printf("2\n");
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_slash);
	}
	if (sig == 3)
	{
		// printf("3\n");
		signal(SIGINT, ctrl_c_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}