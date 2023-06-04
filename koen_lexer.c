#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
	COMMAND,
	OPTION,
	ARGUMENT,
	TOK_SPACE,
	BACKSLASH,
	SEMICOLON,
	SINGLEQ,
	DOUBLEQ,
	DOLLAR,
	REDIRECT_LEFT,
	REDIRECT_RIGHT,
	APPEND_LEFT,
	APPEND_RIGHT,
	PIPE,
	TOK_EOF,	
}	token_type;

typedef struct s_token {
	token_type	type;
	char		*value;
	struct		s_token *next;
}	t_token;



void	print_token(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	if (token_list == NULL)
	{
		printf("List is empty.\n");
		return ;
	}
	while (current != NULL)
	{
		printf("Value has: %s\n", current->value);
		printf("Type is: %d\n", current->type);
		current = current->next;
	}
}

// ft_lstnew
t_token	*create_token(token_type type, const char *value)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = strdup(value);
	token->next = NULL;
	return (token);
}

// ft_lstlast
t_token	*last_token(t_token *token)
{
	if (token)
	{
		while (token)
		{
			if (!token->next)
				return (token);
			token = token->next;
		}
	}
	return (token);
}

// ft_lstadd_back
void	append_token(t_token **token, t_token *new)
{
	if (!*token)
	{
		*token = new;
		return ;
	}
	last_token(*token)->next = new;
}

t_token	*lexer(char *input)
{
	t_token	*head;
	char	*token;

	head = NULL;
	token = strtok(input, " ");
	while (token != NULL)
	{
		if (strcmp(token, "echo") == 0)
		{
			t_token	*tok_cmd = create_token(COMMAND, token);
			append_token(&head, tok_cmd);
		}
		else if (token[0] == '-')
		{
			t_token	*tok_opt = create_token(OPTION, token);
			append_token(&head, tok_opt);
		}
		else if (token[0] == '"')
		{
			t_token	*tok_quote = create_token(DOUBLEQ, token);
			append_token(&head, tok_quote);
			while (token[strlen(token) - 1] != '"')
			{
				token = strtok(NULL, " ");
				strcat(tok_quote->value, " ");
				strcat(tok_quote->value, token);
			}
		}
		else if (token[0] == '$')
		{
			t_token	*tok_dollar = create_token(DOLLAR, token);
			append_token(&head, tok_dollar);
		}
		else
		{
			t_token *tok_arg = create_token(ARGUMENT, token);
			append_token(&head, tok_arg);
		}
		token = strtok(NULL, " ");
	}
	return (head);
}

int	main()
{
	t_token	*token_list;
	char str[43] = "echo hi \"koen\"cheong \"yoo\" hi\" byebye";
	token_list = lexer(str);
	print_token(token_list);
}