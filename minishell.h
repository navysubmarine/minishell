/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:11:38 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/06 17:53:09 by marthoma         ###   ########.fr       */
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

/*pour le parser*/
typedef struct s_cmd
{
	char			**args;
	t_token_type	sep;
	t_cmd			*next;
}					t_cmd;

/*pour le lexer*/
typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	UNKNOWN
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				len;
	struct s_token	*next;
}					t_token;

typedef enum s_state
{
	NORMAL_OUT_WORD,
	NORMAL_IN_WORD,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
	ENV_VARIABLE
}					t_state;

typedef struct s_global
{
	char			*input;
	t_state			state;
	int				i;
	int				word_start;
	t_token			*tok_list;
	t_token			*current;
	int				nbr_pipes;
	t_cmd			*cmd_list;
}					t_global;

/*PARSING - TOKENIZATION OF THE INPUT*/
void				tokenize(t_global *g);
void				init_token(t_global *g);
t_token				*token_new(char *value, t_token_type type);
void				token_add_back(t_token **list, t_token *new);
void				token_clear(t_token **list);
void				token_print(t_token *list);
int					check_tokens(t_token *list);
/*PARSING - TOKENIZATION UTILS : CHAR CARACTERIZATION*/
int					is_whitespace(char c);
int					is_operator_char(char c);
int					is_single_quote(char c);
int					is_double_quote(char c);
/*PARSING - TOKENIZATION : HANDLE EACH TYPE OF CHAR*/
void				handle_whitespace(t_global *g, char *buffer, int *i_buf);
void				handle_operator(t_global *g, char *buffer, int *i_buf);
void				handle_single_quote(t_global *g, char *buffer, int *i_buf);
void				handle_double_quote(t_global *g, char *buffer, int *i_buf);
void				handle_regular_char(t_global *g, char *buffer, int *i_buf);
t_token_type		get_operator_type(const char *str, int *len, t_global *g);
void				flush_word(t_global *g, char *buffer, int *i_buf);
void				process_char(t_global *g, char *buffer, int *i_buf);

#endif