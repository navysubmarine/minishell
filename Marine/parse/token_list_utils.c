/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:34:38 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/03 16:39:47 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_token(t_global *g)
{
	t_token_type	token;
	int				len;
	char			*value;

	token = get_operator_type(&g->input[g->i], &len, g);
	if (token == TOKEN_UNKNOWN)
	{
		printf("Error : unknown token\n");
		exit(1);
	}
	value = ft_substr(g->input, g->i, len);
	token_add_back(&g->tok_list, token_new(value, token));
	free(value);
	g->i += len;
}

t_token	*token_new(char *value, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_token));
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **tok_list, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*tok_list)
	{
		*tok_list = new;
		return ;
	}
	tmp = *tok_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	token_clear(t_token **tok_list)
{
	t_token	*tmp;

	while (*tok_list)
	{
		tmp = (*tok_list)->next;
		free((*tok_list)->value);
		free(*tok_list);
		*tok_list = tmp;
	}
	*tok_list = NULL;
}

void	token_print(t_token *tok_list)
{
	char	*type_str;

	while (tok_list)
	{
		if (tok_list->type == TOKEN_WORD)
			type_str = "WORD";
		else if (tok_list->type == TOKEN_PIPE)
			type_str = "PIPE";
		else if (tok_list->type == TOKEN_REDIRECT_IN)
			type_str = "REDIRECT_IN";
		else if (tok_list->type == TOKEN_REDIRECT_OUT)
			type_str = "REDIRECT_OUT";
		else if (tok_list->type == TOKEN_APPEND)
			type_str = "APPEND";
		else if (tok_list->type == TOKEN_HEREDOC)
			type_str = "HEREDOC";
		else if (tok_list->type == TOKEN_UNKNOWN)
			type_str = "UNKNOWN";
		ft_printf("[%s] %s\n", type_str, tok_list->value);
		tok_list = tok_list->next;
	}
}
