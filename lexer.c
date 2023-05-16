/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:31:58 by mliew             #+#    #+#             */
/*   Updated: 2023/05/16 16:39:33 by mliew            ###   ########.fr       */
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
	TOK_REDIRECT_LEFT,
	TOK_REDIRECT_RIGHT,
	TOK_APPEND_LEFT,
	TOK_APPEND_RIGHT,
	TOK_PIPE,
	TOK_EOF,
};
