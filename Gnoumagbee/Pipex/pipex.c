/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <gcamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:40:59 by gcamara           #+#    #+#             */
/*   Updated: 2026/03/04 17:50:19 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
# include <readline/history.h>
# include <readline/readline.h>

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

void	child_read(int *fd, char *file2)
{
	//int	outfile;

	//close(fd[1]);
	*fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		//close(fd[0]);
		perror_file();
	}
	/*dup2(outfile, STDOUT_FILENO);
	//close(outfile);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);*/
	//ft_create_args(cmd2, envp);
}

void	child_write(int *fd, char *file1)
{

	*fd = open (file1, O_RDONLY);
	if (fd < 0)
	{
		perror_file();
	}
	/*dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (ft_strncmp(file1, "here_doc", ft_strlen(file1)) == 0)
		unlink(file1);*/
	//ft_create_args(cmd1, envp);
}

int	check_argc_pipex(int argc, int *fd)
{
	if (argc != 6)
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

void close_pipe(int cmd, int fd[cmd][2])
{
	int i;

	i = 0;
	while(i < cmd)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void here_doc_in(char *file, char *limiter) 
{
	char *r;
	int here_doc;
	here_doc = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while(1)
	{
		r = readline("Here_doc> ");
		if (r == NULL)
			break;
		if (r != NULL)
		{
			if(ft_strncmp(r, limiter, ft_strlen(limiter)) == 0)
				break;
			write(here_doc, r, ft_strlen(r));
			write(here_doc, "\n", 1);
		}
	}
	close(here_doc);
}

//TODO: count numbers of arguments
//TODO: heredoc or not
//TODO: count numbers of childs
//TODO: child process
int	main(int argc, char **argv, char **envp)
{
	int	status;
	status = 0;
	//int fd[2];
		
	int prev_fd;
	int fd;
	int cmd = (argc - 1) - 3;
	int curr_fd[cmd][2];
	int pid[cmd];
	int i = 0;
	/*if (check_argc_pipex(argc, fd))
		return (1);*/
	
	/* prev fd pour le here doc
	boucle 
	pipe curent pipe
	fork
	prev fd = curent pipe[0]
	Fonction
	ferme le curent pipe[1]
	dup2(prevfd, 0)
	dup2 (currpipe[1], 1)
	*/
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		here_doc_in(argv[1], argv[2]); 
		child_write(&prev_fd, argv[1]);
	}else{
		child_write(&prev_fd, argv[1]);
	}
	while (i < cmd)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
		if (i < cmd)
		{
			if (pipe(curr_fd[i]) == -1)
			{
				perror("Error: Pipe failed");
				exit(1);
			}
		}
		pid[i] = fork();
		if (pid[i] < 0)
			perror_fork();
		if (pid[i] == 0){
			if (i == (cmd - 1))
			{
				child_read(&fd, argv[argc - 1]);
				dup2(fd, 1);
				close(fd);
				//close(curr_fd[i][0]);
			}
			else
			{
				dup2(curr_fd[i][1], 1);
				close(curr_fd[i][1]);
				close(curr_fd[i][0]);
				//printf("cmd %d\n", i);
				close_pipe(i, curr_fd);
			}
			ft_create_args(argv[i + 3], envp);
		}
		//close(prev_fd);
		if (i < cmd - 1)
			prev_fd = curr_fd[i][0];
		close(curr_fd[i][1]);
		i++;
	}
	i = 0;
	while(i < cmd)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		i++;
	}
	return (1);
}
