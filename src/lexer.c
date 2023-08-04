/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:31:58 by mliew             #+#    #+#             */
/*   Updated: 2023/06/05 16:45:30 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static char	*word_dup(const char *str, int start, int finish)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	word = malloc(((finish - start) * sizeof(char)) + 2);
// 	while (start < finish)
// 		word[i++] = str[start++];
// 	word[i] = '\0';
// 	return (word);
// }

static void	split_words(char **array, const char *s, const char *op)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = -1;
	(void)op;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != ' ' && k < 0)
			k = i;
		// if (s[i] == '\"')
		// 	while (s[++i] && s[i] != '\"')
		// 		;
		// else if (s[i] == '\'')
		// 	while (s[++i] && s[i] != '\'')
		// 		;
		// if (ft_strchr(op, s[i]) && s[i] != ' ')
		// {
		// 	k = i;
		// 	if ((s[i] == '>' && s[i + 1] == '>')
		// 		|| (s[i] == '<' && s[i + 1] == '<'))
		// 		i++;
		// 	array[++j] = ft_substr(s, k, i);
		// 	k = -1;
		// }
		if ((s[i + 1] == ' ' || i + 1 == ft_strlen(s)) && k >= 0)
		{
			printf("%s\n", s);
			printf("k: %d |%c|\n", k, s[k]);
			printf("i: %d |%c|\n", i, s[i]);
			array[j++] = ft_substr(s, k, i + 1);
			k = -1;
		}
	}
	array[j] = 0;
}

int	getsize(char *s, const char *op)
{
	int	size;
	int	i;

	i = -1;
	size = 0;
	while (s[++i])
	{
		if (!size)
			size++;
		if (s[i] == '\"')
			while (s[++i] != '\"')
				;
		else if (s[i] == '\'')
			while (s[++i] != '\'')
				;
		if ((s[i] == ' ' && s[i - 1] != ' ')
			|| (ft_strchr(op, s[i]) && s[i - 1] != ' '))
			size++;
	}
	return (size);
}

char	**lexer(char *s, const char *op)
{
	char		**array;

	if (!s)
		return (NULL);
	printf("SIZE: %d\n", getsize(s, op));
	array = malloc((sizeof(char *) * getsize(s, op)) + 1);
	if (!array)
		return (NULL);
	split_words(array, s, op);
	for (int i = 0; array[i]; i++)
		printf("array[%d]: [%s]\n", i , array[i]);
	return (array);
}
