/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:36:33 by mliew             #+#    #+#             */
/*   Updated: 2023/06/05 15:36:28 by mliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line_bonus.h"

// main
char	**get_input(char *cwd, char **envp);

// utils
void	sigint_handler(int sig);
void	myexit(int status);

// build_ins
void	call_echo(char **input);
void	call_cd(char **input, char *cwd);
void	call_unset(char **input, char **envp);
void	call_export(char **input, char **envp);
void	export2(char **input, char **envp);

// executable
void	cmd(char **input, char *cwd, char **ev);
int		executable(char **input, char **ev);

// lexer
char	**check_dollar(char **array, char **envp);
int		check_quotes(char const *s);
char	**lexer(char const *s);

// pipex

#endif