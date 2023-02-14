/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:54 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/14 14:01:20 by olahmami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**split_path;
	char	**join_path;
	int		i;
	int		fd[2];
	pid_t	pid1;
	int		infile;
	char	**split_cmd;
	char	*executable;
	pid_t	pid2;
	int		outfile;
}			t_pipex;

char		*cmd_extand(t_pipex *p);
void		fork_cmd(t_pipex *p, char *argv[], char **envp);
char		**read_env(t_pipex *p, char **envp);
void		cmd1(t_pipex *p, char **argv, char **envp);
void		cmd2(t_pipex *p, char **argv, char **envp);
void		execution(t_pipex *p, char **envp);

#endif