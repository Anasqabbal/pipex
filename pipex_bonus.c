/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/28 23:42:43 by anqabbal         ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
	t_d f;
	int fd[2];
	int	n_pipe;
	int pid;
	int i;

	f.fd1 = creat_open_file(av[1], 0);
	f.fd2 = creat_open_file(av[ac - 1], 1);
	n_pipe = ac - 3;
	i = -1;
	while (++i < ac - 3)
	{
		if (pipe(fd) == -1)
			exit (1);
		int pid = fork();
		if (pid == -1)
			ft_printf("exit with error\n");
		else if (pid == 0)
			ft_printf("do command number %d", i);
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
	return (0);
}