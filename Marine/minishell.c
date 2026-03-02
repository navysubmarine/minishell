/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/03/02 14:20:45 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*cwd;
	char		*rl;
	t_global	g;
	int			i;

	i = 0;
	while (i < 10)
	{
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
		if (g.list)
		{
			ft_printf("Tokens:\n");
			token_print(g.list);
			token_clear(&g.list);
		}
		free(g.input);
		rl_clear_history();
		i++;
	}
	return (0);
}
