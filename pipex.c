/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:51:31 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/23 17:02:24 by anqabbal         ###   ########.fr       */
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
	//ft_printf("UUUU\n");
}

void	child_process_(char *cmd, char **env, int *fd)
{
	ft_printf("IN CHILD\n");
	close (fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)// write into
		ft_printf("error");
	do_command(cmd, env);
	close (fd[1]);
}

void parent_process_(char *cmd, char **env, int *fd)
{
	ft_printf("IN PARENT\n");
	// int fileout;
	// fileout = open(, O_CREAT | O_RDWR, 0777);
	// dup2(fileout, 1);
	close (fd[1]);
//	close (fileout);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_printf("error");
	do_command(cmd, env);
	close(fd[0]);
	//close (fileout);
}

int main(int ac, char **av, char **env)
{
	t_d f;
	static int ii;
	int fd[2];
	int pid;
	int pid1;

	if (ac != 5)
		return (1);
	else
	{
		// f.fd1 = creat_open_file(av[1], 0);
		// f.fd2 = creat_open_file(av[4], 1);
		if (pipe(fd) == -1)
			exit (1);
		pid = fork();
		if (pid == -1)
			exit (1);
		if (pid == 0)
		{
			ft_printf("chi i == %d\n", ii++);
			child_process_(av[2], env, fd);
		}
		pid1 = fork();
		if (pid1 == 0)
		{
			ft_printf("par i == %d\n", ii++);
			parent_process_(av[3], env, fd);
		}
		// waitpid(pid, NULL, 0);
		// waitpid(pid1, NULL, 0);
		close(fd[1]);
		close(fd[0]);
		wait(NULL);
		wait(NULL);
	}
	return (0);
}
