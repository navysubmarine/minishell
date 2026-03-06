/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <gcamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:56:11 by gcamara           #+#    #+#             */
/*   Updated: 2026/02/23 11:07:39 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_fork(void)
{
	perror("Fork");
	exit(1);
}

void	perror_file(void)
{
	perror("Error");
	exit(1);
}

void	perror_path(void)
{
	write(2, "Error : Path does not exist ", 28);
	write(2, "\n", 1);
	exit(127);
}

void	perror_cmd(void)
{
	write(2, "Error: Command not found", 24);
	write(2, "\n", 1);
	exit(1);
}
