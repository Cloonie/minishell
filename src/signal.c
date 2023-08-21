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

void	quitsubshell(int sig)
{
	(void)sig;
	printf("1111\n");
}

void	newprompt(int sig)
{
	(void)sig;
	ft_printf("\n");
	// rl_replgitace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(int num)
{
	if (num == 0)
	{
		signal(SIGINT, newprompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == 1)
	{
		signal(SIGINT, quitsubshell);
	}
	// else if (num == 2)
}