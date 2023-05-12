/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:58:39 by mliew             #+#    #+#             */
/*   Updated: 2022/06/03 21:35:29 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (0);
	array = malloc(count * size);
	if (!array)
		return (0);
	ft_bzero(array, count * size);
	return (array);
}
