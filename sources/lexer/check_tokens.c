/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:57:35 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/06 16:08:54 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirect(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	check_tokens(t_token *list)
{
	t_token *current;
	if (!list)
	{
		/*cas d'erreur*/
		return (0);
	}
	current = list;
	if (current->type != TOKEN_WORD)
	{
		/*cas d'erreur ou l'input commence par un separateur*/
		printf("syntax error near unexpected token `%s'\n", list->value);
		return (0);
	}
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				/*cas d'erreur ou le pipe n'est pas suivi par un mot */
				printf("syntax error near unexpected token `%s'\n",
					list->value);
				return (0);
			}
		}
		if (is_redirect(current->type))
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				/*cas d'erreur ou il n'y a pas de fichier vers lequel envoyer
				la redirection. ici on verifie seulement que c'est un mot
				on verifiera au moment de l'expand si il y a un fichier ou non*/
				printf("syntax error near unexpected token `%s'\n",
					list->value);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}