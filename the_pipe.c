/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:01:21 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/18 16:06:58 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	the_pipe(t_d *f)
{
	int	fd;
	(void) fd;

	//ft_printf("the command line[1] == %s\n", f->cmd1[0]);
	// fd = dup2(f->fd1, 1);
	// if (fd < 0)
	// {
	// 	perror("dup");
	// 	ft_clear(0, 1, f);
	// }
	prepare_path(f->cmd1[0], f);
	//printf("the path is %s\n", f->path);
	if (execve(f->path, f->cmd1, NULL) == -1)
		perror("execve");

}