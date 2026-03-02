/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:11:38 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/02 15:40:58 by marthoma         ###   ########.fr       */
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

#ifndef MAX_LEN
# define MAX_LEN 1000
#endif

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
	TOKEN_OR,
	TOKEN_UNKNOWN
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				i_start;
	int				len;
	struct s_token	*next;
}					t_token;

typedef enum s_state
{
	NORMAL_OUT_WORD,
	NORMAL_IN_WORD,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
}					t_state;

typedef struct s_global
{
	char			*input;
	t_state			state;
	int				i;
	int				word_start;
	t_token			*list;
	t_token			*current;
}					t_global;

void				tokenize(t_global *g);
t_token				*token_new(char *value, t_token_type type);
void				token_add_back(t_token **list, t_token *new);
void				token_clear(t_token **list);
void				token_print(t_token *list);

#endif