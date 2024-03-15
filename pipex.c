/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:51:31 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/15 16:00:56 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av)
{
	t_d f;

	if (ac != 5)
		return (1);
	else
	{
		f.fd1 = creat_open_file(av[1]);
		f.fd2 = creat_open_file(av[4]);
		prepare_commands(av[2], av[3], &f);
		the_pipe(&f);
	}
	close (f.fd1);
	close (f.fd2);
	split_free(f.cmd1, split_strlen(av[2], ' ', 0));
	split_free(f.cmd2, split_strlen(av[3], ' ', 0));
	return (0);
}