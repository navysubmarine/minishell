/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <gcamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:47:56 by gcamara           #+#    #+#             */
/*   Updated: 2026/02/03 19:51:09 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_create_args(char *cmd, char **envp)
{
	char	*paths;
	char	**args;
	char	**tab;

	if (!cmd || cmd[0] == '\0')
		perror_cmd();
	if (access(cmd, X_OK | F_OK) == 0)
		ft_execpath(cmd, envp);
	paths = search_path(envp, "PATH=");
	if (paths == NULL || paths[0] == '\0')
		perror_path();
	tab = ft_split(paths, ':');
	if (tab == NULL)
	{
		ft_free_tab(tab);
		exit(1);
	}
	args = ft_split(cmd, ' ');
	if (args == NULL)
	{
		ft_free_tab(args);
		ft_free_tab(tab);
		exit(1);
	}
	ft_exec(tab, args, envp);
}

void	ft_execpath(char *cmd, char **envp)
{
	char	*args[2];

	args[0] = cmd;
	args[1] = NULL;
	execve(args[0], args, envp);
}

void	ft_exec(char **tab, char **args, char **envp)
{
	int		i;
	char	*exec;

	i = 0;
	while (tab[i] != NULL)
	{
		exec = ft_strjoin_char(tab[i], args[0], "/");
		if (access(exec, X_OK) == 0)
			execve(exec, args, envp);
		free(exec);
		i++;
	}
	perror("Error execve");
	ft_free_tab(tab);
	ft_free_tab(args);
	exit(127);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

char	*search_path(char **envp, char *variable)
{
	int	i;
	int	j;
	int	len;
	int	max;

	i = 0;
	len = 0;
	max = strlen(variable);
	while (envp[i] != NULL)
	{
		len = 0;
		j = 0;
		while (j <= max && len <= max)
		{
			if (envp[i][j] == variable[len])
				len++;
			j++;
			if (len == max)
				return (&envp[i][j]);
		}
		i++;
	}
	return (NULL);
}
