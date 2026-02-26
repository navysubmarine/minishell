/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/26 10:00:00 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}

static t_token_type	get_operator_type(const char *str, int *len)
{
	*len = 1;
	if (str[0] == '|')
	{
		if (str[1] == '|')
			return (*len = 2, TOKEN_OR);
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
	if (str[0] == '&')
	{
		if (str[1] == '&')
			return (*len = 2, TOKEN_AND);
	}
	if (str[0] == 39)
		return (TOKEN_SINGLEQUOTE);
    //todo : bloquer les meta-characters dans les quotes
    if (str[0] == 34)
        return (TOKEN_DOUBLEQUOTE);
    //todo : bloquer les meta-characters dans les double quotes, sauf $
	return (TOKEN_WORD);
}

static char	*extract_word(const char *str, int *start, int *end)
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
		else if (list->type == TOKEN_SINGLEQUOTE)
			type_str = "SINGLEQUOTE";
		else if (list->type == TOKEN_DOUBLEQUOTE)
			type_str = "DOUBLEQUOTE";
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
	t_token	*list;
	int		i;
	int		op_len;
	char	*word;

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
			get_operator_type(&input[i], &op_len);
			word = ft_substr(input, i, op_len);
			token_add_back(&list, 
				token_new(word, get_operator_type(&input[i], &op_len)));
			free(word);
			i += op_len;
		}
		else
		{
			word = extract_word(input, &i, &i);
			if (word && ft_strlen(word) > 0)
				token_add_back(&list, token_new(word, TOKEN_WORD));
			free(word);
		}
	}
	return (list);
}
