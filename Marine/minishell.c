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
	char cwd[1024];
	char *rl;
	int i = 0;

	// shell is running in interactive mode
//	if (isatty(STDIN_FILENO))
	while (i < 10)
	{
		// accept input from user and execute commands
		getcwd(cwd, sizeof(cwd));
		rl = readline(cwd);
		tokenize(rl);
		//ft_printf("%s\n", rl);
		//ft_echo(rl);
		rl_clear_history();
		i++;
	}
	
	// shell is running in non interactive mode
	// else
	// {
	// 	// execute commands from script
		
	// }

	return (0);
}

void	tokenize(char *rl)
{
	char **tokens;
	int i = 0;

	tokens = ft_split(rl, ' ');
	while (tokens[i])
	{
		ft_printf("%s\n", tokens[i]);
		i++;
	}
}
