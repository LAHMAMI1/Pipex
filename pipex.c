/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:51 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/12 05:31:37 by olahmami         ###   ########.fr       */
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
	if ((p->infile = open(argv[1], O_RDONLY, 0644)) == -1)
	{
		perror("");
		exit(127);
	}
	dup2(p->infile, 0);
	dup2(p->fd[1], 1);
	p->split_cmd = ft_split(argv[2], ' ');
	if (access(p->split_cmd[0], F_OK | X_OK) < 0)
	{
		if (ft_strchr(p->split_cmd[0], '/'))
		{
			ft_putstr_fd("pipex: no such file or directory: ", 2);
			ft_putendl_fd(p->split_cmd[0], 2);
			exit(127);
		}
		p->split_path = read_env(p, envp);
		p->i = 0;
		while (p->split_path[p->i])
		{
			p->executable = ft_strjoin(p->split_path[p->i], p->split_cmd[0]);
			if (access(p->executable, F_OK | X_OK) == 0)
				return(p->executable);
			free(p->executable);
			p->i++;
		}
	}
	else if (access(p->split_cmd[0], F_OK | X_OK) == 0)
		p->executable = p->split_cmd[0];
	return(p->executable);
}

char *cmd2(t_pipex *p, char **argv,char **envp)
{
	close(p->fd[1]);
	if ((p->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		perror("");
		exit(127);
	}
	dup2(p->outfile, 1);
	dup2(p->fd[0], 0);
	p->split_cmd = ft_split(argv[3], ' ');
	if (access(p->split_cmd[0], F_OK | X_OK) < 0)
	{
		if (ft_strchr(p->split_cmd[0], '/'))
		{
			ft_putstr_fd("pipex: no such file or directory: ", 2);
			ft_putendl_fd(p->split_cmd[0], 2);
			exit(127);
		}
		p->split_path = read_env(p, envp);
		p->i = 0;
		while (p->split_path[p->i])
		{
			p->executable = ft_strjoin(p->split_path[p->i], p->split_cmd[0]);
			if (access(p->executable, F_OK | X_OK) == 0)
				return(p->executable);
			free(p->executable);
			p->i++;
		}
	}
	else if (access(p->split_cmd[0], F_OK | X_OK) == 0)
		p->executable = p->split_cmd[0];
	return(p->executable);
}

void execution(t_pipex *p, char **envp)
{
	if (execve(p->executable, p->split_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(p->split_cmd[0], 2);
		exit(127);
	}
}

int main(int argc, char *argv[], char **envp)
{
	t_pipex p;

	if (pipe(p.fd) == -1)
	{
		perror("");
		exit(127);
	}
	if (argc == 5)
	{
		p.pid1 = fork();
		if (p.pid1 < 0)
		{
			perror("");
			exit(127);
		}
		if (p.pid1 == 0)
		{
			cmd1(&p, argv, envp);
			execution(&p, envp);
		}
		p.pid2 = fork();
		if (p.pid2 < 0)
		{
			perror("");
			exit(127);
		}
		if (p.pid2 == 0)
		{
			cmd2(&p, argv, envp);
			execution(&p, envp);
		}
		close(p.fd[0]);
		close(p.fd[1]);
		waitpid(p.pid1, NULL, 0);
		waitpid(p.pid2, NULL, 0);
	}
	else
	{
		perror("");
		exit(127);
	}
}
