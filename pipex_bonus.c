/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/30 16:55:38 by anqabbal         ###   ########.fr       */
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

	f.fd1 = creat_open_file(av[1], 0);
	f.fd2 = creat_open_file(av[ac - 1], 1);
	f.ac = ac;
	fd = creat_pipes(ac - 3);
	if (!fd)
		return (1);
	f.i = 1;
	while (++f.i < ac - 1)
	{
		pid = fork();
		if (pid == 0 && f.i == 2)
			first_command(av[f.i], env, fd, &f);
		else if (pid == 0 && f.i != 2 && f.i != ac - 2)
			mid_command(av[f.i], env, fd, &f);
		else if (pid == 0 && f.i == ac - 2)
			last_command(av[f.i], env, fd, &f);
		pid2 = fork();
		if (pid2 == 0 && f.i + 1 == ac - 2)
			last_command(av[f.i + 1], env, fd, &f);
		else if (pid2 == 0 && f.i + 1 < ac - 2)
			mid_command(av[f.i + 1], env, fd, &f);
		else if  (pid2 == 0 && f.i == ac - 2)
		{
			clear_pipes(fd, ac - 3);
			ft_clear(&f);
			exit(0);
		}
		else
		{
			clear_pipes(fd, ac - 3);
			ft_clear(&f);
			while (wait(NULL) != -1);
		}
	}
	return (0);
}
