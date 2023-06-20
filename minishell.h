/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:36:33 by mliew             #+#    #+#             */
/*   Updated: 2023/06/20 00:29:09 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
#include <fcntl.h>

# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line_bonus.h"

typedef	struct	s_pipe {
	int		numcmd;
	int		tmpin;
	int		tmpout;
	int		argc;
	int		here_doc_flag;
	char	**argv;
	char	**envp;
}	t_pipe;

// # define Ctrl(x) ((x) & 0x1f)

// main
char	**get_input(char *cwd);

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
void	executable(char **input, char **ev);

// lexer

// pipex

#endif