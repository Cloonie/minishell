/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew < mliew@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:31:58 by mliew             #+#    #+#             */
/*   Updated: 2023/04/12 22:13:02 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {
	TOK_BACKSLASH,
	TOK_SEMICOLON,
	TOK_SINGLEQ,
	TOK_DOUBLEQ,
	TOK_DOLLAR,
	TOK_LA,
	TOK_RA,
	TOK_DLA,
	TOK_DRA,
	TOK_PIPE,
	TOK_ENV_VAR,
	TOK_DOLLAR_QM,
	TOK_EOF,
};

typedef struct {
	int type;
	int value;
} token_t;

int get_token(char **expr) {
	static const char *operators = "/;'";
	while (isspace(**expr)) {
		(*expr)++;
	}
	if (**expr == '\0') {
		return TOK_EOF;
	}
	if (isdigit(**expr)) {
		int value = 0;
		while (isdigit(**expr)) {
			value = value * 10 + (**expr - '0');
			(*expr)++;
		}
		return TOK_NUM;
	}
	if (strchr(operators, **expr) != NULL) {
		int type = strchr(operators, **expr) - operators + TOK_ADD;
		(*expr)++;
		return type;
	}
	return TOK_EOF;
}

int main() {
	char expr[256];
	token_t token;
	printf("Enter an arithmetic expression: ");
	fgets(expr, 256, stdin);
	char *p = expr;
	while ((token.type = get_token(&p)) != TOK_EOF) {
		printf("Type: %d\n", token.type);
	}
	return 0;
}
