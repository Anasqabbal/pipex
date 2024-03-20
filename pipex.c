/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:51:31 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/20 14:48:59 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **env)
{
	t_d f;

	if (ac != 5)
		return (1);
	else
	{
		f.fd1 = creat_open_file(av[1]);
		f.fd2 = creat_open_file(av[4]);
		prepare_commands(av[2], av[3], &f);
		the_pipe(&f, env);
	}
	return (0);
}