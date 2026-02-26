/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:11:38 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/25 15:25:00 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>
# include <curses.h>
# include <stdio.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <unistd.h> 
# include <stdlib.h> 
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include "includes/ft_printf/ft_printf.h"
# include "includes/libft/libft.h"

void    ft_echo(char *rl);
void	tokenize(char *rl);

#endif