/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:13:27 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/06 18:05:53 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_sep(t_token_type *current)
{
	if (current == PIPE || current == REDIRECT_IN || current == REDIRECT_OUT
		|| current == APPEND || current == HEREDOC)
	{
		return (1);
	}
	return (0);
}

void	init_cmd(t_global *g)
{
	char			*args;
	t_token_type	sep;
	t_token			*current;

	if (!g->tok_list)
		return ;
	current = g->tok_list;
	while (current)
	{
		if (is_sep(current->type))
		{
			cmd_new(args, )
		}
	current = current->next;	
	}
}

t_cmd	*cmd_new(char *s, t_token_type sep)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_cmd));
	new->args = ft_split(s, 31);
	if (!new->args)
	{
		free(new);
		return (NULL);
	}
	new->sep = sep;
	new->next = NULL;
	return (new);
}

void	cmd_add_back(t_cmd **cmd_list, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return ;
	if (!*cmd_list)
	{
		*cmd_list = new;
		return ;
	}
	tmp = *cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// void	init_cmd(t_global *g)
// {
// 	t_token 		*current;
// 	t_cmd			cmd;
// 	char			*args;
// 	t_token_type	sep;

// 	token = get_operator_type(&g->input[g->i], &len, g);
// 	if (token == UNKNOWN)
// 	{
// 		printf("Error : unknown token\n");
// 		exit(1);
// 	}
// 	value = ft_substr(g->input, g->i, len);
// 	token_add_back(&g->tok_list, token_new(value, token));
// 	free(value);
// 	g->i += len;
// }

void	parse(t_global *g)
{
	init_cmd(g);
	current = g->tok_list;
	while (current)
	{
		current = current->next;
	}
}