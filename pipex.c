/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:51:31 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/26 11:46:03 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	creat_open_file(char *f1, int ind)
{
	int	fd;

	if (ind == 0)
		fd = open(f1, O_RDONLY);
	else
		fd = open(f1, O_CREAT | O_RDWR, 0777);
	if (fd < 0)
	{
		perror("open");
		exit (1);
	}
	return (fd);
}

void	do_command(char *cmd, char **env, t_d *f)
{
	char *path;
	char **cmd1;

	cmd1 = ft_split(cmd,  ' ');
	if (!cmd1)
	{
		ft_clear(f);
		exit (1);
	}
	path = check__path(cmd1[0] , env);
	if (!path)
	{
		ft_clear(f);
		exit (1);
	}
	if (execve(path, cmd1, env) == -1)
	{
		ft_clear(f);
		exit(1);
	}
}

void	child_process_(char *cmd, char **env, int *fd, t_d *f)
{
	close (fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		ft_clear(f);
		exit(1);
	}
	if (dup2(f->fd1, STDIN_FILENO) == -1)
	{
		ft_clear(f);
		exit(1);
	}
	close (fd[1]);
	do_command(cmd, env, f);
}
void	fi()
{
	system("leaks pipex");
}

void parent_process_(char *cmd, char **env, int *fd, t_d *f)
{
	close (fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		ft_clear(f);
		exit(1);
	}
	// if (dup2(f->fd2, STDOUT_FILENO) == -1)
	// {
	// 	ft_clear(f);
	// 	exit(1);
	// }
	close(fd[0]);
	do_command(cmd, env, f);
}



int main(int ac, char **av, char **env)
{
	t_d f;
	int fd[2];
	int pid;

	atexit(fi);
	if (ac != 5)
		return (1);
	else
	{
		f.fd1 = creat_open_file(av[1], 0);
		f.fd2 = creat_open_file(av[4], 1);
		if (pipe(fd) == -1)
			exit (1);
		pid = fork();
		if (pid == -1)
			return (ft_clear(&f), 1);
		if (pid == 0)
		{
			parent_process_(av[3], env, fd, &f);
		}
		else
			child_process_(av[2], env, fd, &f);
	}
	return (ft_clear(&f), 0);
}
