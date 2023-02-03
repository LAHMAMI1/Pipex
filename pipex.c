/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:51 by olahmami          #+#    #+#             */
/*   Updated: 2023/02/03 05:41:07 by olahmami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**read_env(char *envp)
{
	char *path;
	char **split_path = ft_calloc(1, 1);
	size_t len;
	
	len = ft_strlen(envp);
	path = ft_substr(envp, 5, len);
	split_path = ft_split(path, ':');
	return (split_path);
}

int main(int argc, char const *argv[], char **envp)
{
	char **split_path = read_env(envp[6]);
	printf("%s\n", split_path[0]);
  return 0;
}
