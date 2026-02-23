/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <gcamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:40:59 by gcamara           #+#    #+#             */
/*   Updated: 2026/02/03 19:23:36 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_char(char const *s1, char const *s2, char *s)
{
	int		char_count;
	char	*copy;

	char_count = ft_strlen(s1) + ft_strlen (s2) + 1;
	copy = malloc(sizeof(char) * char_count + 1);
	if (copy == NULL)
		return (NULL);
	copy[0] = '\0';
	ft_strlcat(copy, s1, ft_strlen(s1) + 1);
	ft_strlcat(copy, s, ft_strlen(s1) + 2);
	ft_strlcat(copy, s2, char_count + 1);
	return (copy);
}

void	child_read(int *fd, char *cmd2, char *file2, char **envp)
{
	int	outfile;

	close(fd[1]);
	outfile = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		close(fd[0]);
		perror_file();
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_create_args(cmd2, envp);
}

void	child_write(int *fd, char *file1, char *cmd1, char **envp)
{
	int	infile;

	close(fd[0]);
	infile = open (file1, O_RDONLY);
	if (infile < 0)
	{
		close(fd[1]);
		perror_file();
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_create_args(cmd1, envp);
}

int	check_argc_pipex(int argc, int *fd)
{
	if (argc != 5)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("Error: Pipe failed");
		exit(1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid_1;
	int	pid_2;
	int	status;

	status = 0;
	if (check_argc_pipex(argc, fd))
		return (1);
	pid_1 = fork();
	if (pid_1 < 0)
		perror_fork();
	if (pid_1 == 0)
		child_write(fd, argv[1], argv[2], envp);
	pid_2 = fork();
	if (pid_2 < 0)
		perror_fork();
	if (pid_2 == 0)
		child_read(fd, argv[3], argv[4], envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
