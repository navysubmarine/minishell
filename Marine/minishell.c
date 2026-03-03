/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/03 16:16:55 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_global_struct(t_global *g)
{
	if (!g)
		return ;
	memset(g, 0, sizeof(t_global));
	g->state = NORMAL_OUT_WORD;
}

int	main(void)
{
	char		*cwd;
	t_global	g;
	// int			i;

	// i = 0;
	init_global_struct(&g);
	// while (i < 10)
	// {
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_printf("Error: getcwd failed\n");
			return (1);
		}
		g.input = readline(cwd);
		free(cwd);
		if (!g.input)
		{
			ft_printf("Error : readline failed\n");
			return (1);
		}
		tokenize(&g);
		if (g.tok_list)
		{
			ft_printf("Tokens:\n");
			token_print(g.tok_list);
			token_clear(&g.tok_list);
		}
		free(g.input);
		rl_clear_history();
	// 	i++;
	// }
	return (0);
}
