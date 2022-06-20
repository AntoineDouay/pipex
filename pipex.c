/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:34:38 by adouay            #+#    #+#             */
/*   Updated: 2022/06/20 18:19:51 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_args(int ac, char **av)
{
	if (ac < 5)
		return (1);
	if (access(av[1], F_OK | R_OK) == -1)
		return (1);
	if (access(av[ac - 1], F_OK | W_OK) == -1)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];

	char	*ls_option[3] = 	{"ls", "-l", NULL};
	char	*wc_option[3] = 	{"wc", "-l", NULL};

	if (parse_args(ac, av))
		return (0);

	pipe(fd);

	int	pid = fork();

	if (pid == -1)
		return (0);
	if (pid == 0)
		printf("child\n");
	if (pid > 0)
		printf("parent\n");
	
//	char	*options[3] = 	{"ls", "-a", NULL};
//	execve("/usr/bin/ls", options, envp);
	return (0);
}
