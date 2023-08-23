/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:19:06 by mliew             #+#    #+#             */
/*   Updated: 2023/08/21 11:19:06 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit3(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
}

void	quitsubshell(int sig)
{
	(void)sig;
	printf("\n");
}

void	sigint_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(int num)
{
	if (num == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == 1)
	{
		signal(SIGINT, quitsubshell);
		signal(SIGQUIT, quit3);
	}
}
