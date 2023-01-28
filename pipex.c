/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:35:51 by olahmami          #+#    #+#             */
/*   Updated: 2023/01/28 02:23:49 by olahmami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char const *argv[])
{
	int id = fork(); // = 0
	int n, i;

	if (id == 0)
		n = 1;
	else
		n = 6;
	for (i = n; i < n + 5; i++)
		printf("%d ",i);
	if (id != 0)
		wait(NULL);
	
	return 0;
}
