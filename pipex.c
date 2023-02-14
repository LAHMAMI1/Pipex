/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:51 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/14 14:51:05 by olahmami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execution(t_pipex *p, char **envp)
{
	if (execve(p->executable, p->split_cmd, envp) == -1)
	{
		if (!access(p->executable, F_OK | X_OK))
			exit(0);
		else if (!access(p->executable, F_OK))
		{
			ft_putstr_fd("pipex: permission denied: ", 2);
			ft_putendl_fd(p->split_cmd[0], 2);
			exit(126);
		}
		else
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(p->split_cmd[0], 2);
			exit(127);
		}
	}
}

void	cmd2(t_pipex *p, char **argv, char **envp)
{
	close(p->fd[1]);
	p->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p->outfile == -1)
	{
		perror("");
		exit(1);
	}
	dup2(p->outfile, 1);
	dup2(p->fd[0], 0);
	p->split_cmd = ft_split(argv[3], ' ');
	p->split_path = read_env(p, envp);
	cmd_extand(p);
}

void	cmd1(t_pipex *p, char **argv, char **envp)
{
	close(p->fd[0]);
	p->infile = open(argv[1], O_RDONLY, 0644);
	if (p->infile == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(argv[1], 2);
		exit(1);
	}
	dup2(p->infile, 0);
	dup2(p->fd[1], 1);
	p->split_cmd = ft_split(argv[2], ' ');
	p->split_path = read_env(p, envp);
	cmd_extand(p);
}

void	fork_cmd(t_pipex *p, char *argv[], char **envp)
{
	p->pid1 = fork();
	if (p->pid1 < 0)
	{
		perror("");
		exit(1);
	}
	if (p->pid1 == 0)
	{
		cmd1(p, argv, envp);
		execution(p, envp);
	}
	p->pid2 = fork();
	if (p->pid2 < 0)
	{
		perror("");
		exit(1);
	}
	if (p->pid2 == 0)
	{
		cmd2(p, argv, envp);
		execution(p, envp);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	p;
	int		status;

	if (pipe(p.fd) == -1)
		exit(1);
	if (argc == 5)
	{
		fork_cmd(&p, argv, envp);
		close(p.fd[0]);
		close(p.fd[1]);
		waitpid(p.pid1, NULL, 0);
		waitpid(p.pid2, &status, 0);
		exit(WEXITSTATUS(status));
	}
	else
	{
		ft_putstr_fd("Pipex: Invalid number of arguments\n", 2);
		exit(1);
	}
}
