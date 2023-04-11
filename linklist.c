/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:32:46 by mliew             #+#    #+#             */
/*   Updated: 2023/04/10 11:32:46 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

def struct s_linklist
{
	char		character;
	int			num;
	struct s_linklist	*next;
} t_koen;

int	main(void)
{
	t_koen *node;

	node = malloc(sizeof(t_koen));
	node->next = malloc(sizeof(t_koen));
	node->num = 69;
	node->next->character = 'K';
	printf("%c\n", node->next->character);
}
