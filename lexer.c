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

int	handle_token(char c)
{
	if (c == ' ')
		return (TOK_SPACE);
	else if (c == '\"')
		return (TOK_DOUBLEQ);
	else if (c == '\'')
		return (TOK_SINGLEQ);
	else if (c == '>')
		return (TOK_REDIRECT_RIGHT);
	else if (c == '<')
		return (TOK_REDIRECT_LEFT);
	else if (c == '$')
		return (TOK_DOLLAR);
	else if (c == '|')
		return (TOK_PIPE);
	else
		return (TOK_EOF);
}

// void	lexer(char **input)
// {
// 	int		i;
// 	int		j;
// 	t_list	*list;

// 	i = 0;
// 	j = 0;
// 	list = ft_lstnew("void");
// 	list->var = input[i];
// 	while (input[++i])
// 	{
// 		while (input[i][j])
// 			handle_token(input[i][j]);
// 	}
// }