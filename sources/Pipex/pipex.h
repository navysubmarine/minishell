/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <gcamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:03:43 by gcamara           #+#    #+#             */
/*   Updated: 2026/03/04 15:00:11 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>

void	child_read(int *fd, char *file2);
void	child_write(int *fd, char *file1);
char	*search_path(char **envp, char *variable);
char	*ft_strjoin_char(char const *s1, char const *s2, char *s);
void	ft_create_args(char *cmd, char **envp);
void	ft_exec(char **tab, char **args, char **envp);
void	ft_free_tab(char **tab);
int		check_argc_pipex(int argc, int *fd);
void	ft_execpath(char *cmd, char **envp);
void	perror_file(void);
void	perror_path(void);
void	perror_cmd(void);
void	perror_fork(void);

#endif