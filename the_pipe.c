/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:01:21 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/15 16:06:46 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	the_pipe(t_d *f)
{
	int	fd;

	fd = dup2(f.fd1, 1);
	if (fd < 0)
	{
		split_free(f->cmd1, f->l_cmd1);
		split_free(f->cmd1, f->l_cmd1);
		perror("dup");
	}
	

}