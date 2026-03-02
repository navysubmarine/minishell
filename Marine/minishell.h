/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:11:38 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/02 11:56:19 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf/ft_printf.h"
#include "includes/libft/libft.h"
#include <curses.h>
#include <dirent.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLEQUOTE,
	TOKEN_DOUBLEQUOTE,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_UNKNOWN
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

// void    echo(char *rl);
t_token				*tokenize(char *input);
t_token				*token_new(char *value, t_token_type type);
void				token_add_back(t_token **list, t_token *new);
void				token_clear(t_token **list);
void				token_print(t_token *list);

#endif