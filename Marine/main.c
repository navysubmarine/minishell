/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/23 16:19:00 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	// the current directory
	char cwd[1024];
	char *input;

	input = argv[1];
	// shell is running in interactive mode
	if (isatty(STDIN_FILENO))
	{
		getcwd(cwd, sizeof(cwd));
		
		// accept input from user and execute commands
	}
	// shell is running in non interactive mode
	else
	{
		// execute commands from script
	}
}