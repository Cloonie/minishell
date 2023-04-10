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

int	main(void)
{
	struct s_linklist *node;

	node = malloc(sizeof(struct s_linklist));
	node->next = malloc(sizeof(struct s_linklist));
	node->num = 69;
	node->next->character = 'K';
	printf("%c\n", node->next->character);
}
