/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:34:30 by adouay            #+#    #+#             */
/*   Updated: 2022/06/22 20:01:45 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

#include "libft/libft.h"
#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>

typedef struct s_pipex{

	int		ppid;
	int		pid;
	int		infile_fd;
	int		outfile_fd;
	int		commands_nbr;
	int		pipe_nbr;
	int		*pipe;
	char	**cmds;
	char 	*path_line;
	char	**paths;
}	t_pipex;

void	create_child(t_pipex *pipex);

#endif
