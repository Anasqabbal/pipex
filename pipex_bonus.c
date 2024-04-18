/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/04/01 14:29:52 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int    **creat_pipes(int ac)
{
	int	**fd;
	int i;

	i = 0;
	fd = malloc(sizeof(int *) * ac);
	if (!fd)
		return (NULL);
	while(i < ac)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (fds_free(fd, i));
		if (pipe(fd[i]) == -1)
			return (fds_free(fd, i + 1));
		i++;
	}
	return (fd);
}

int main(int ac, char **av, char **env)
{
	t_d f;
	int **fd;
	int pid;
	int pid2;

	f.i = 1;
	f.p = 0;
	f.fd1 = creat_open_file(av[1], 0);
	f.fd2 = creat_open_file(av[ac - 1], 1);
	f.ac = ac;
	fd = creat_pipes(ac - 4);
	if (!fd)
		return (1);
	while (f.p < ac - 4)
	{
		ft_printf("[the pipe is %d]\n", f.p);
		f.i++;
		pid = fork();
		if (pid < 0)
			ft_printf("error with fork(1)\n");
		if (pid == 0 && f.i == 2)
		{
			ft_printf("command == %s \nnext command == %s\nF1_", av[f.i],  av[f.i + 1]);
			first_command(av[f.i], env, fd, &f);
		}
		else if (pid == 0 && f.i != 2 && f.i != ac - 2)
		{
			ft_printf("command == %s \nnext command == %s\nF1_", av[f.i],  av[f.i + 1]);
			mid_command(av[f.i], env, fd, &f);
		}
		else if (pid == 0 && f.i == ac - 2)
		{
			ft_printf("command == %s \nnext command == %s\nF1_", av[f.i],  av[f.i + 1]);
			last_command(av[f.i], env, fd, &f);
		}
		pid2 = fork();
		if (pid2 < 0)
			ft_printf("error with fork(2)\n");
		if (pid2 == 0 && f.i + 1 == ac - 2)
		{
			ft_printf("command == %s \nnext command == %s\nF2_", av[f.i],  av[f.i + 1]);
			last_command(av[f.i + 1], env, fd, &f);
		}
		else if (pid2 == 0 && f.i + 1 < ac - 2)
		{
			ft_printf("command == %s \nnext command == %s\nF2_", av[f.i],  av[f.i + 1]);
			mid_command(av[f.i + 1], env, fd, &f);
		}
		else if  (pid2 == 0 && f.i == ac - 2)
		{
			ft_printf("command == %s \nnext command == %s\nF2_", av[f.i],  av[f.i + 1]);
			clear_pipes(fd, ac - 4);
			ft_clear(&f);
			exit(0);
		}
		else
		{
			close(fd[f.p][0]);
			close(fd[f.p][1]);
			close(f.fd1);
			waitpid(pid, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
		if ((ac - 3) % 2 == 0)
			f.p++;
		f.i++;
		f.p++;
	}
	return (close(f.fd2), 0);
}
