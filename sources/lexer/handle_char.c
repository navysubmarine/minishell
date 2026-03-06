/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:10:54 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/03 18:11:53 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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