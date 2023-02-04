/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:51 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/03 23:32:00 by olahmami         ###   ########.fr       */
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
	path =NULL;
	split_path =NULL;
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

void cmd1(char *av1, char *av2)
{
	int fd;
	
}

int main(int argc, char const *argv[], char **envp)
{
	char **split_path = read_env(envp);
	pid_t pid1;

	if (argc == 5)
	{
		pid1 = fork();
		if (pid1 == 0)
			cmd1(argv[1], argv[2]);		
		
	}
	printf("%s\n", split_path[1]);
  return 0;
}
