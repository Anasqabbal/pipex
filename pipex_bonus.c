/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/27 10:18:42 by anqabbal         ###   ########.fr       */
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
	int pid;

	f.fd1 = creat_open_file(av[1], 0);
	f.fd2 = creat_open_file(av[4], 1);
	ft_printf("")
	
	return (ft_clear(&f), 0);
}