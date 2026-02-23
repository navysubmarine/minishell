/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:24:05 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/23 11:07:55 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*we need to check if the she is running in interactive
mode or not. interactive mode = we are able to give it
input, and it will execute commands. non-interactive mode =
you cannot give it input, it executes commands from a script.
To know, we use the isatty function*/
int	main(int argc, char **argv)
{
	// the current directory
	char cwd[1024];
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