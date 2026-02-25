/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/25 11:43:32 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char cwd[1024];
	char *rl;

	// shell is running in interactive mode
	if (isatty(STDIN_FILENO))
	{
		// accept input from user and execute commands
		getcwd(cwd, sizeof(cwd));
		rl = readline(cwd);
		ft_printf("%s\n", rl);
	}
	// shell is running in non interactive mode
	else
	{
		// execute commands from script
	}
	return (0);
}