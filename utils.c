/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:57:42 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/14 14:51:00 by olahmami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**read_env(t_pipex *p, char **envp)
{
	char	*path;
	size_t	len;

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
	free(path);
	p->i = 0;
	while (p->split_path[p->i])
	{
		p->join_path[p->i] = ft_strjoin(p->split_path[p->i], "/");
		free(p->split_path[p->i]);
		p->i++;
	}
	return (p->split_path);
}

char	*cmd_extand(t_pipex *p)
{
	p->i = 0;
	while (p->split_path[p->i])
	{
		p->executable = ft_strjoin(p->split_path[p->i], p->split_cmd[0]);
		if (access(p->executable, F_OK) == 0)
		{
			if (ft_strchr(p->split_cmd[0], '/'))
				break ;
			return (p->executable);
		}
		free(p->executable);
		p->i++;
	}
	if (access(p->split_cmd[0], F_OK) == 0 && ft_strchr(p->split_cmd[0], '/'))
		p->executable = p->split_cmd[0];
	else if ((access(p->split_cmd[0], F_OK == -1)) && ft_strchr(p->split_cmd[0],
			'/'))
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(p->split_cmd[0], 2);
		exit(127);
	}
	return (p->executable);
}
