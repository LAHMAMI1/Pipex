/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:51 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/05 07:59:16 by olahmami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**read_env(char **envp)
{
	char *path;
	char **split_path;
	size_t len;
	int i;

	i = 0;
	path = NULL;
	split_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			len = ft_strlen(envp[i]);
			path = ft_substr(envp[i], 5, len);
		}
		i++;
	}
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		split_path[i] = ft_strjoin(split_path[i], "/");
		i++;
	}
	return (split_path);
}

void cmd1(char *infile, char *cmd1, char **envp)
{
	
	
}

int main(int argc, char const *argv[], char **envp)
{
	char **split_path;
	int fd[2];
	pid_t pid1;
	pid_t pid2;

	split_path = read_env(envp);
	if (pipe(fd) == -1)
		return 1;
	if (argc == 5)
	{
		pid1 = fork();
		if (pid1 < 0)
			exit(1);
		if (pid1 == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			cmd1(fd[1], argv[2], envp);
		}
		pid2 = fork();
		if (pid2 < 0)
			exit(1);
		if (pid2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			
		}
		close(fd[1]);
		close(fd[0]);

		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	
  return 0;
}
