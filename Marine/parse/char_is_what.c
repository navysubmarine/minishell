/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_is_what.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:36:21 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/03 16:41:24 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_single_quote(char c)
{
	return (c == 39);
}

int	is_double_quote(char c)
{
	return (c == 34);
}
