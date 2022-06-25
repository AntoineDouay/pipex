/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:34:38 by adouay            #+#    #+#             */
/*   Updated: 2022/06/25 19:31:38 by adouay           ###   ########.fr       */
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

int	get_files(int ac, char **av, t_pipex *pipex)
{
	pipex->infile_fd = open(av[1], O_RDONLY);
	pipex->outfile_fd = open(av[ac - 1], O_WRONLY);
	if (pipex->infile_fd == -1)
		return (1);
	if (pipex->outfile_fd == -1)
		return (1);
	return (0);
}

int	get_commands(char **av, t_pipex *pipex)
{
	int i;

	i = 0;
	pipex->cmds = malloc(sizeof(char *) * (pipex->commands_nbr + 1));
	if (!pipex->cmds)
		return (1);
	while (i < pipex->commands_nbr)
	{
		pipex->cmds[i] = av[i + 2];
		i++;
	}
	pipex->cmds[i] = 0;
	return (0);
}

char	*path_finding(char **envp)
{
	int	i;

	i = 0;
	while(ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	return (envp[i]);
}

void	free_double_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		free (tab[i]);
		i++;
	}
	free (tab[i]);
	free (tab);
	return ;
}

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipe = malloc(sizeof(int) * (2 * pipex->pipe_nbr));
	while (i < pipex->pipe_nbr)
	{
		if (pipe(pipex->pipe + (2 * i)) < 0)
			return ;  // ERROR
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (parse_args(ac, av))
		return (0);
	if (get_files(ac, av, &pipex))
		return (0);
	
	pipex.commands_nbr = ac - 3;
	pipex.pipe_nbr = ac - 4;
	pipex.cmds_pos = -1;
	if (get_commands(av, &pipex))
		return (0);
	pipex.path_line = path_finding(envp) + 5;
	pipex.paths = ft_split(pipex.path_line, ':');
	create_pipes(&pipex);
	while (++(pipex.cmds_pos) < pipex.commands_nbr)
		create_child(&pipex, envp);
	close_pipes(&pipex);
	close(pipex.infile_fd);
	close(pipex.outfile_fd);
	free (pipex.pipe);
	free (pipex.cmds);
	free_double_array(pipex.paths);
	return (0);
}
