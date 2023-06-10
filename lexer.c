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

#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
	TOK_EOF,
	TOK_SPACE,
	TOK_BACKSLASH,
	TOK_SEMICOLON,
	TOK_SINGLEQ,
	TOK_DOUBLEQ,
	TOK_DOLLAR,
	TOK_REDIRECT_LEFT,
	TOK_REDIRECT_RIGHT,
	TOK_APPEND_LEFT,
	TOK_APPEND_RIGHT,
	TOK_PIPE,
};

static int	count_words(char const *s)
{
	int		words;

	words = 0;
	while (*s)
	{
		if (*s != ' ')
		{
			++words;
			while (*s && *s != ' ')
				++s;
		}
		else
			++s;
	}
	return (words);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (str[start] == '\"' && str[finish - 1] == '\"')
		finish--;
	else if (str[start] == '\'' && str[finish - 1] == '\'')
		finish--;
	while (start < finish)
	{
		while (str[start] == '\"')
			start++;
		while (str[start] == '\'')
			start++;
		word[i++] = str[start++];
	}
	word[i] = '\0';
	return (word);
}

static void	split_words(char **array, const char *s)
{
	int		i; // string index
	int		j; // array index
	int		k; // start index

	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != ' ' && k < 0)
			k = i;
		else if ((s[i] == ' ' || i == ft_strlen(s)) && k >= 0)
		{
			array[j++] = word_dup(s, k, i);
			k = -1;
		}
		if (s[i] == '\"')
		{
			if (s[i - 1] == ' ')
				k = i;
			while (s[i] && s[++i] != '\"')
				;
		}
		else if (s[i] == '\'')
		{
			if (s[i - 1] == ' ')
				k = i;
			while (s[i] && s[++i] != '\'')
				;
		}
		i++;
	}
	array[j] = 0;
}

char	**check_dollar(char **array, char **envp)
{
	int		i;
	int		j;
	char	*str;
	char	*var;

	i = -1;
	j = -1;
	while (array[++i])
	{
		while (envp[++j] && array[i][0] == '$')
		{
			var = &array[i][1];
			str = ft_substr(envp[j], 0, ft_strpos(envp[j], "="));
			if (ft_strncmp(str, var, ft_strlen(array[i])) == 0)
				array[i] = ft_strchr(envp[j], '=') + 1;
			else if (!envp[j + 1])
				array[i] = "";
		}
	}
	return (array);
}

int	check_quotes(char const *s)
{
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	while (*s)
	{
		if (*s == '\"')
			d_quote++;
		if (*s == '\'')
			s_quote++;
		s++;
	}
	if ((d_quote % 2) != 0 || (s_quote % 2) != 0)
	{
		printf("Error quotes are not closed.\n");
		return (1);
	}
	return (0);
}

char	**lexer(char const *s)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc((count_words(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (check_quotes(s))
	{
		free(array);
		return (array);
	}
	split_words(array, s);
	return (array);
}

// int	main()
// {
// 	char	**array;

// 	array = lexer(" \'abc echo\' koen \"hey world there\" ");
// 	for (int i = 0; array[i]; i++)
// 		printf("String %d: |%s|\n", i, array[i]);
// 	// system("leaks a.out");
// 	// printf("%d\n", is_special_char('\"'));
// }

// int	is_special_char(char c)
// {
// 	if (c == ' ')
// 		return (TOK_SPACE);
// 	else if (c == '\"')
// 		return (TOK_DOUBLEQ);
// 	else if (c == '\'')
// 		return (TOK_SINGLEQ);
// 	else if (c == '>')
// 		return (TOK_REDIRECT_RIGHT);
// 	else if (c == '<')
// 		return (TOK_REDIRECT_LEFT);
// 	else if (c == '$')
// 		return (TOK_DOLLAR);
// 	else if (c == '|')
// 		return (TOK_PIPE);
// 	else
// 		return (TOK_EOF);
// }