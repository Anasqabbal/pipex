/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:51:31 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/23 11:03:39 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_files(t_p *e)
{
	if (e->fd[0] != -1)
		close(e->fd[0]);
	if (e->fd[1] != -1)
		close(e->fd[1]);
	if (e->fd0 != -1)
		close(e->fd0);
	if (e->fd1 != -1)
		close(e->fd1);
}

int	creat_open_file(char *f1, int ind)
{
	int	fd;

	if (ft_strncmp(f1, "/dev/stdin", 10) == 0 && ind != 0)
	{
		ft_putstr_fd("pipex: /dev/stdin:", 2);
		ft_putendl_fd(" Permission denied", 2);
		return (fd = -1, fd);
	}
	if (ind == 0)
		fd = open(f1, O_RDONLY);
	else
	{
		fd = open(f1, O_CREAT | O_RDWR, 0644);
	}
	if (fd < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(f1);
		fd = -1;
	}
	return (fd);
}

int	ft_execve1(t_p *e, int in, int out, int i)
{
	e->pid = fork();
	if (e->pid < 0)
		return (perror("fork"), 1);
	if (e->pid == 0)
	{
		if (i == 2)
			close(e->fd[0]);
		else if (i == 3)
			close(e->fd[1]);
		if ((in == -1 && i == 2) || (i == 3 && out == -1))
			exit (1);
		if (dup2(in, STDIN_FILENO) < 0)
			return (perror("dup2"), 1);
		if (dup2(out, STDOUT_FILENO) < 0)
			return (perror("dup2"), 1);
		close_files(e);
		do_command(e->av[i], e->env, e);
	}
	return (0);
}

void	init_struct(int ac, char **av, char **env, t_p *e)
{
	e->fd0 = creat_open_file(av[1], 0);
	e->fd1 = creat_open_file(av[4], 1);
	e->env = env;
	e->ac = ac;
	e->av = av;
}

int	main(int ac, char **av, char **env)
{
	t_p	e;
	int	status;

	if (ac != 5)
		return (ft_putstr_fd("invalid arguments\n", 2), EXIT_FAILURE);
	else
	{
		init_struct(ac, av, env, &e);
		if (pipe(e.fd) == -1)
			return (perror("pipe"), 1);
		if (!ft_execve1(&e, e.fd0, e.fd[1], 2))
		{
			if (ft_execve1(&e, e.fd[0], e.fd1, 3))
				return (close_files(&e), 1);
		}
		else
			return (close_files(&e), 1);
		close_files(&e);
		while (waitpid(-1, &status, 0) != -1)
			;
	}
	return (WEXITSTATUS(status));
}
