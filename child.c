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

void	make_dup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while(i < pipex->pipe_nbr * 2)
	{
		close (pipex->pipe[i]);
		i++;
	}
}

char	*get_cmd_path(t_pipex *pipex)
{
	char	*tmp;
	int	i;

	i = 0;
	if(access(pipex->cmd_options[0], F_OK | R_OK) == 0)
		return (pipex->cmd_options[0]);
	while (pipex->paths[i] != 0)
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		tmp = ft_strjoin(tmp, pipex->cmd_options[0]);
		if(access(tmp, F_OK | R_OK) == 0)
			return (tmp);
		free (tmp);
		i++;
	}
	tmp = NULL;
	return (tmp);
}

void	create_child(t_pipex *pipex, char **envp)
{
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		if(pipex->cmds_pos == 0)
			make_dup(pipex->infile_fd, pipex->pipe[1]);
		else if(pipex->cmds_pos == pipex->commands_nbr - 1)
			make_dup(pipex->pipe[pipex->cmds_pos * 2 - 2], pipex->outfile_fd);
		else
			make_dup(pipex->pipe[pipex->cmds_pos * 2 - 2], pipex->pipe[pipex->cmds_pos * 2 + 1]);
		close_pipes(pipex);
		pipex->cmd_options = ft_split(pipex->cmds[pipex->cmds_pos], ' ');
		pipex->cmd_path = get_cmd_path(pipex);
		execve(pipex->cmd_path, pipex->cmd_options, envp);		
	}
}
