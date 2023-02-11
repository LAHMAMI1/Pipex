/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:54 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/11 02:10:43 by olahmami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "Libft/libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pipex
{
	char **split_path;
	int i;
	int fd[2];
	pid_t pid1;
	int infile;
	char **split_cmd;
	char *executable;
	pid_t pid2;
	int outfile;
} t_pipex;


#endif