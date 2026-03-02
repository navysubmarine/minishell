/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/02 11:56:41 by marthoma         ###   ########.fr       */
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

static int	is_quote(char c)
{
	return (c == 39 || c == 34);
}

static t_token_type	get_operator_type(const char *str, int *len)
{
	*len = 1;
	if (str[0] == '|')
	{
		return (TOKEN_PIPE);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (*len = 2, TOKEN_APPEND);
		return (TOKEN_REDIRECT_OUT);
	}
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (*len = 2, TOKEN_HEREDOC);
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
	char	*final;

	*len = 1;
	if (str[0] == 39)
	{
		if (ft_strchr(str, 39))
		{
			final = ft_strchr(str, 39);
			*len = (final - str) - 1;
		}
	}
	if (str[0] == 34)
	{
		if (ft_strchr(str[1], 34))
		{
			final = ft_strchr(str, 34);
			*len = (final - str) - 1;
		}
	}
	return (TOKEN_WORD);
}

static char	*extract_normal_word(const char *str, int *start, int *end)
{
	int		i;
	char	*word;

	i = *start;
	while (str[i] && !is_whitespace(str[i]) && !is_operator_char(str[i]))
		i++;
	word = ft_substr(str, *start, i - *start);
	*end = i;
	return (word);
}

static char	*extract_quoted_word(const char *str, int *start, int *end)
{
	int		i;
	char	*word;
	char	*dol_sign;
	int 	len;

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
		else if (list->type == TOKEN_AND)
			type_str = "AND";
		else if (list->type == TOKEN_OR)
			type_str = "OR";
		else
			type_str = "UNKNOWN";
		ft_printf("[%s] %s\n", type_str, list->value);
		list = list->next;
	}
}

t_token	*tokenize(char *input)
{
	t_token			*list;
	int				i;
	int				op_len;
	char			*word;
	t_token_type	type;

	list = NULL;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (is_whitespace(input[i]))
		{
			i++;
			continue ;
		}
		if (is_operator_char(input[i]))
		{
			type = get_operator_type(&input[i], &op_len);
			word = ft_substr(input, i, op_len);
			token_add_back(&list, token_new(word, type));
			free(word);
			i += op_len;
		}
		if (is_quote(input[i]))
		{
			type = get_quote_type(&input[i], &op_len);
			word = extract_quoted_word(input, &i, &op_len);
			token_add_back(&list, token_new(word, type));
			free(word);
			i += op_len;
		}
		else
		{
			word = extract_normal_word(input, &i, &i);
			if (word && ft_strlen(word) > 0)
				token_add_back(&list, token_new(word, TOKEN_WORD));
			free(word);
		}
	}
	return (list);
}
