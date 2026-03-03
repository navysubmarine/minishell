/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/03 16:51:54 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token_type	get_operator_type(const char *str, int *len, t_global *g)
{
	*len = 1;
	if (str[0] == '|')
	{
		g->nbr_pipes++;
		printf("nbr_pipes = %d\n", g->nbr_pipes);
		return (TOKEN_PIPE);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>')
		{
			*len = 2;
			return (TOKEN_APPEND);
		}
		return (TOKEN_REDIRECT_OUT);
	}
	if (str[0] == '<')
	{
		if (str[1] == '<')
		{
			*len = 2;
			return (TOKEN_HEREDOC);
		}
		return (TOKEN_REDIRECT_IN);
	}
	return (TOKEN_UNKNOWN);
}

void	flush_word(t_global *g, char *buffer, int *i_buf)
{
	if (*i_buf > 0)
	{
		buffer[*i_buf] = '\0';
		token_add_back(&g->tok_list, token_new(buffer, TOKEN_WORD));
		*i_buf = 0;
		buffer[0] = '\0';
	}
}

void	handle_whitespace(t_global *g, char *buffer, int *i_buf)
{
	if (g->state == NORMAL_IN_WORD)
	{
		flush_word(g, buffer, i_buf);
		g->state = NORMAL_OUT_WORD;
	}
	else if (*i_buf > 0 && (g->state == IN_SINGLE_QUOTE
			|| g->state == IN_DOUBLE_QUOTE))
	{
		buffer[(*i_buf)++] = g->input[g->i];
	}
	g->i++;
}

void	handle_operator(t_global *g, char *buffer, int *i_buf)
{
	flush_word(g, buffer, i_buf);
	init_token(g);
}

void	handle_single_quote(t_global *g, char *buffer, int *i_buf)
{
	if (g->state == IN_SINGLE_QUOTE)
		g->state = NORMAL_IN_WORD;
	else if (g->state == NORMAL_OUT_WORD || g->state == NORMAL_IN_WORD)
		g->state = IN_SINGLE_QUOTE;
	else
		buffer[(*i_buf)++] = g->input[g->i];
	g->i++;
}

void	handle_double_quote(t_global *g, char *buffer, int *i_buf)
{
	if (g->state == IN_DOUBLE_QUOTE)
		g->state = NORMAL_IN_WORD;
	else if (g->state == NORMAL_OUT_WORD || g->state == NORMAL_IN_WORD)
		g->state = IN_DOUBLE_QUOTE;
	else
		buffer[(*i_buf)++] = g->input[g->i];
	g->i++;
}

void	handle_regular_char(t_global *g, char *buffer, int *i_buf)
{
	if (g->state == NORMAL_OUT_WORD)
		g->state = NORMAL_IN_WORD;
	if (*i_buf < MAX_LEN - 1)
		buffer[(*i_buf)++] = g->input[g->i];
	g->i++;
}

void	process_char(t_global *g, char *buffer, int *i_buf)
{
	if (is_whitespace(g->input[g->i]))
		handle_whitespace(g, buffer, i_buf);
	else if (is_operator_char(g->input[g->i]) && g->state != IN_SINGLE_QUOTE
		&& g->state != IN_DOUBLE_QUOTE)
		handle_operator(g, buffer, i_buf);
	else if (is_single_quote(g->input[g->i]))
		handle_single_quote(g, buffer, i_buf);
	else if (is_double_quote(g->input[g->i]))
		handle_double_quote(g, buffer, i_buf);
	else
		handle_regular_char(g, buffer, i_buf);
}

void	tokenize(t_global *g)
{
	char	buffer[MAX_LEN];
	int		i_buf;

	i_buf = 0;
	buffer[0] = '\0';
	if (!g->input)
		return ;
	while (g->input[g->i])
		process_char(g, buffer, &i_buf);
	if (g->state == IN_SINGLE_QUOTE || g->state == IN_DOUBLE_QUOTE)
	{
		printf("Error: unclosed quote\n");
		token_clear(&g->tok_list);
		exit(1);
	}
	flush_word(g, buffer, &i_buf);
}

// void	tokenize(t_global *g)
// {
// 	char	buffer[MAX_LEN];
// 	int		i_buf;

// 	i_buf = 0;
// 	buffer[0] = '\0';
// 	if (!g->input)
// 	{
// 		printf("");
// 		// todo : free all
// 		return ;
// 	}
// 	while (g->input[g->i])
// 	{
// 		if (is_whitespace(g->input[g->i]))
// 		{
// 			if (g->state == NORMAL_IN_WORD)
// 			{
// 				if (i_buf > 0)
// 				{
// 					buffer[i_buf] = '\0';
// 					token_add_back(&g->tok_list, token_new(buffer, TOKEN_WORD));
// 					i_buf = 0;
// 					buffer[0] = '\0';
// 				}
// 				g->state = NORMAL_OUT_WORD;
// 			}
// 			else if (i_buf > 0 && (g->state == IN_SINGLE_QUOTE
// 					|| g->state == IN_DOUBLE_QUOTE))
// 			{
// 				buffer[i_buf++] = g->input[g->i];
// 			}
// 			g->i++;
// 		}
// 		else if (is_operator_char(g->input[g->i]) && g->state != IN_SINGLE_QUOTE
// 			&& g->state != IN_DOUBLE_QUOTE)
// 		{
// 			if (i_buf > 0)
// 			{
// 				buffer[i_buf] = '\0';
// 				token_add_back(&g->tok_list, token_new(buffer, TOKEN_WORD));
// 				i_buf = 0;
// 				buffer[0] = '\0';
// 			}
// 			init_token(g);
// 		}
// 		else if (is_single_quote(g->input[g->i]))
// 		{
// 			if (g->state == IN_SINGLE_QUOTE)
// 				g->state = NORMAL_IN_WORD;
// 			else if (g->state == NORMAL_OUT_WORD || g->state == NORMAL_IN_WORD)
// 				g->state = IN_SINGLE_QUOTE;
// 			if (g->state == IN_DOUBLE_QUOTE)
// 				buffer[i_buf++] = g->input[g->i];
// 			g->i++;
// 		}
// 		else if (is_double_quote(g->input[g->i]))
// 		{
// 			if (g->state == IN_DOUBLE_QUOTE)
// 				g->state = NORMAL_IN_WORD;
// 			else if (g->state == NORMAL_OUT_WORD || g->state == NORMAL_IN_WORD)
// 				g->state = IN_DOUBLE_QUOTE;
// 			if (g->state == IN_SINGLE_QUOTE)
// 				buffer[i_buf++] = g->input[g->i];
// 			g->i++;
// 		}
// 		else
// 		{
// 			if (g->state == NORMAL_OUT_WORD)
// 				g->state = NORMAL_IN_WORD;
// 			if (i_buf < MAX_LEN - 1)
// 				buffer[i_buf++] = g->input[g->i];
// 			g->i++;
// 		}
// 	}
// 	if (g->state == IN_SINGLE_QUOTE || g->state == IN_DOUBLE_QUOTE)
// 	{
// 		printf("Error: unclosed quote\n");
// 		token_clear(&g->tok_list);
// 		exit(1);
// 	}
// 	if (i_buf > 0)
// 	{
// 		buffer[i_buf] = '\0';
// 		token_add_back(&g->tok_list, token_new(buffer, TOKEN_WORD));
// 	}
// }
