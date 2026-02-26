/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/25 15:22:18 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*cwd;
	char	*rl;
	t_token	*tokens;
	int		i;

	i = 0;
	while (i < 10)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_printf("Error: getcwd failed\n");
			return (1);
		}
		rl = readline(cwd);
		free(cwd);
		if (!rl)
		{
			ft_printf("Error : readline failed\n");
			return (1);
		}
		tokens = tokenize(rl);
		if (tokens)
		{
			ft_printf("Tokens:\n");
			token_print(tokens);
			token_clear(&tokens);
		}
		free(rl);
		rl_clear_history();
		i++;
	}
	return (0);
}

// void	tokenize(char *rl)
// {
// 	char **tokens;
// 	int i = 0;

// 	tokens = ft_split(rl, ' ');
// 	while (tokens[i])
// 	{
// 		ft_printf("%s\n", tokens[i]);
// 		i++;
// 	}
// }
