/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:51 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/10 04:49:07 by olahmami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**read_env(t_pipex *p, char **envp)
{
	char *path;
	size_t len;

	p->i = 0;
	path = NULL;
	p->split_path = NULL;
	while (envp[p->i])
	{
		if (ft_strncmp(envp[p->i], "PATH=", 5) == 0)
		{
			len = ft_strlen(envp[p->i]);
			path = ft_substr(envp[p->i], 5, len);
		}
		p->i++;
	}
	p->split_path = ft_split(path, ':');
	p->i = 0;
	while (p->split_path[p->i])
	{
		p->split_path[p->i] = ft_strjoin(p->split_path[p->i], "/");
		p->i++;
	}
	return (p->split_path);
}

char *cmd1(t_pipex *p, char **argv,char **envp)
{
	close(p->fd[0]);
	p->infile = open(argv[1], O_RDONLY);
	dup2(p->infile, 0);
	dup2(p->fd[1], 1);
	p->split_cmd = ft_split(argv[2], ' ');
	if (access(p->split_cmd[0], F_OK | X_OK) < 0)
	{
		p->split_path = read_env(&p, envp);
		p->i = 0;
		while (p->split_path[p->i])
		{
			p->executable = ft_strjoin(p->split_path, p->split_cmd[0]);
			if (access(p->executable, F_OK | X_OK) == 0)
				return(p->executable);
			p->i++;
		}
	}
	else
		p->executable = p->split_cmd[0];
	return(p->executable);
}

void execution(t_pipex *p, char **envp)
{
	if (execve(p->executable, p->split_cmd, envp) == -1)
	{
		ft_putstr_fd("Error", 2);
		exit(127);
	}
}

int main(int argc, char const *argv[], char **envp)
{
	t_pipex p;

	if (pipe(p.fd) == -1)
		return 1;
	if (argc == 5)
	{
		p.pid1 = fork();
		if (p.pid1 < 0)
			exit(1);
		if (p.pid1 == 0)
		{
			cmd1(&p, argv, envp);
			execution(&p, envp);
		}
		p.pid2 = fork();
		if (p.pid2 < 0)
			exit(1);
		if (p.pid2 == 0)
		{
			close(p.fd[1]);
			dup2(p.fd[0], 0);
			close(p.fd[0]);
			
		}
		waitpid(p.pid1, NULL, 0);
		waitpid(p.pid2, NULL, 0);
	}
	
  return 0;
}
