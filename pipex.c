/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:51:31 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/25 16:11:39 by anqabbal         ###   ########.fr       */
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

void	do_command(char *cmd, char **env)
{
	char *path;
	char **cmd1;

	cmd1 = ft_split(cmd,  ' ');
	if (!cmd1)
		return ;
	path = check__path(cmd1[0] , env);
	if (!path)
		exit (1);
	if (execve(path, cmd1, env) == -1)
	{
		ft_printf("command not found\n");
		exit(1);
	}
}

void	child_process_(char *cmd, char **env, int *fd, t_d *f)
{
	ft_printf("IN CHILD\n");
	close (fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)// write into
		ft_printf("error");
	if (dup2(f->fd1, STDIN_FILENO) == -1)
		ft_printf("error");
	close (fd[1]);
	do_command(cmd, env);
}

void parent_process_(char *cmd, char **env, int *fd, t_d *f)
{
	ft_printf("IN PARENT\n");
	close (fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_printf("error");
	if (dup2(f->fd2, STDOUT_FILENO) == -1)
		ft_printf("error");
	close(fd[0]);
	do_command(cmd, env);
}

int main(int ac, char **av, char **env)
{
	t_d f;
	int fd[2];
	int pid;

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
			exit (1);
		if (pid == 0)
			parent_process_(av[3], env, fd, &f);
		else
			child_process_(av[2], env, fd, &f);
	}
	return (0);
}
