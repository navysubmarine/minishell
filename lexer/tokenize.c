/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/06 12:11:59 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*todo : verifier la syntaxe, detecter si elle est valide
mais necessite d'etre completee. L'input ne doit pas commencer
par un separateur - les separateurs doivent etre bien places, pas
deux a la suite, les quotes doivent etre fermees et les redirections
ont un fichier cible*/

t_token_type	get_operator_type(const char *str, int *len, t_global *g)
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
