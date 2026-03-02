/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/02 16:07:50 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

static int	is_single_quote(char c)
{
	return (c == 39);
}

static int	is_double_quote(char c)
{
	return (c == 34);
}

static t_token_type	get_operator_type(t_global *g)
{
	g->current_token->len = 1;
	if (g->current_token->value[0] == '|')
	{
		return (TOKEN_PIPE);
	}
	if (g->current_token->value[0] == '>')
	{
		if (g->current_token->value[1] == '>')
		{
			g->current_token->len = 2;
			return (TOKEN_APPEND);
		}
		return (TOKEN_REDIRECT_OUT);
	}
	if (g->current_token->value[0] == '<')
	{
		if (g->current_token->value[1] == '<')
		{
			g->current_token->len = 2;
			return (TOKEN_HEREDOC);
		}
		return (TOKEN_REDIRECT_IN);
	}
	return (TOKEN_UNKNOWN);
}

static void	print_env_var(char *str, int len)
{
	char	*var;
	char	*tmp;

	tmp = str;
	tmp[len] = '\0';
	var = getenv(tmp);
	printf("%s", var);
}

static t_token_type	get_quote_type(const char *str, int *len)
{
	if (str[0] == 39)
	{
		if (ft_strchr(str + 1, 39))
		{
			final = ft_strchr(str + 1, 39);
			*len = final - str;
		}
		else
			*len++;
	}
	if (str[0] == 34)
	{
		if (ft_strchr(str + 1, 34))
		{
			final = ft_strchr(str + 1, 34);
			*len = final - str;
		}
		else
			*len++;
	}
	return (TOKEN_WORD);
}

static char	*extract_normal_word(const char *str, int *start)
{
	int		i;
	char	*word;

	i = *start;
	while (str[i] && !is_whitespace(str[i]) && !is_operator_char(str[i]))
		i++;
	word = ft_substr(str, *start, i - *start);
	return (word);
}

static char	*extract_quoted_word(const char *str, int *start, int *end)
{
	int		i;
	char	*word;
	char	*dol_sign;
	int		len;

	i = *start;
	len = 0;
	while (str[i] != 34 && str[i] != 39)
	{
		if (ft_strchr(str, '$') && ft_strchr(str, '$') < ft_strchr(str[1], 34))
		{
			dol_sign = ft_strchr(str, '$');
			len = dol_sign;
			while ((str[len] > 64 && str[len] < 91) || str[len] == '_')
			{
				len++;
			}
			print_env_var(str, len);
		}
		while (str[i])
			i++;
		word = ft_substr(str, *start, i - *start);
		*end = i;
	}
	return (word);
}

t_token	*token_new(char *value, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
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

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	token_clear(t_token **list)
{
	t_token	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	token_print(t_token *list)
{
	char	*type_str;

	while (list)
	{
		if (list->type == TOKEN_WORD)
			type_str = "WORD";
		else if (list->type == TOKEN_PIPE)
			type_str = "PIPE";
		else if (list->type == TOKEN_REDIRECT_IN)
			type_str = "REDIRECT_IN";
		else if (list->type == TOKEN_REDIRECT_OUT)
			type_str = "REDIRECT_OUT";
		else if (list->type == TOKEN_APPEND)
			type_str = "APPEND";
		else if (list->type == TOKEN_HEREDOC)
			type_str = "HEREDOC";
		else
			type_str = "UNKNOWN";
		ft_printf("[%s] %s\n", type_str, list->value);
		list = list->next;
	}
}

void	init_token_op(t_global *g)
{
	g->current = &(g->input[g->i]);
	g->current->type = get_operator_type(&g);
	if (g->current->type == TOKEN_UNKNOWN)
	{
		printf("Error : unknown token\n");
		// todo: free all
		exit(1);
	}
	g->current->value = ft_substr(g->input, g->i, g->current->len);
	token_add_back(g->list, token_new(g->current->value, g->current->type));
	g->i += g->current->len;
}

void	tokenize(t_global *g)
{
	t_token	*list;
	char	buffer[MAX_LEN];
	int		i_buf;

	i_buf = 0;
	list = NULL;
	g->i = 0;
	g->state = NORMAL_OUT_WORD;
	g->list = list;
	g->current = list;
	if (!g->input)
	{
		printf("Error : invalid input");
		// todo : free all
		exit(1);
	}
	while (g->input[g->i])
	{
		if (is_whitespace(g->input[g->i]))
		{
			if (g->state == NORMAL_IN_WORD)
			{
				if (ft_strlen(buffer) > 0)
					token_add_back(&g->list, token_new(buffer, TOKEN_WORD));
				buffer[0] = '\0';
				i_buf = 0;
				g->state = NORMAL_OUT_WORD;
			}
			g->i++;
		}
		else if (is_operator_char(g->input[g->i]))
		{
			if (g->state == IN_SINGLE_QUOTE || g->state == IN_DOUBLE_QUOTE)
			{
				g->i++;
			}
			else
				init_token_op(&g);
		}
		else if (is_single_quote(g->input[g->i]))
		{
			if (g->state == IN_SINGLE_QUOTE)
			{
				g->state = NORMAL_OUT_WORD;
				if (ft_strlen(buffer) > 0)
					token_add_back(&g->list, token_new(buffer, TOKEN_WORD));
				buffer[0] = '\0';
				i_buf = 0;
				g->i++;
			}
			else if (g->state == IN_DOUBLE_QUOTE)
			{
				buffer[i_buf++] = g->input[g->i];
				g->i++;
			}
			else
			{
				g->state = IN_SINGLE_QUOTE;
				g->i++;
			}
		}
		else if (is_double_quote(g->input[g->i]))
		{
			if (g->state == IN_DOUBLE_QUOTE)
			{
				g->state = NORMAL_OUT_WORD;
				if (ft_strlen(buffer) > 0)
					token_add_back(&g->list, token_new(buffer, TOKEN_WORD));
				buffer[0] = '\0';
				i_buf = 0;
				g->i++;
			}
			else if (g->state == IN_DOUBLE_QUOTE)
			{
				buffer[i_buf++] = g->input[g->i];
				g->i++;
			}
			else
			{
				g->state = IN_DOUBLE_QUOTE;
				g->i++;
			}
		}
		else
		{
			if (g->state == IN_SINGLE_QUOTE || g->state == IN_DOUBLE_QUOTE)
			{
				g->i++;
			}
			else
			{
				g->current->value = extract_normal_word(g->input, g->i);
				if (g->current->value && ft_strlen(g->current->value) > 0)
					token_add_back(g->list, token_new(g->current->value,
							TOKEN_WORD));
			}
		}
	}
}
