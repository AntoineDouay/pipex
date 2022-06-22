/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:06:22 by adouay            #+#    #+#             */
/*   Updated: 2022/06/22 21:28:21 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_child(t_pipex *pipex)
{
	int	i;
	int pid;

	i = 0;
	while (i < pipex->commands_nbr)
	{
		pid = fork();
		if(pid == 0)
		{
			printf("i'm a child my id is : %d, my parent id is %d\n", getpid(), getppid());
		}
		i++;
	}
}