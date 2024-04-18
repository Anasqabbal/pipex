/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:15:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/04/15 15:33:15 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_files(t_d *f, int indice)
{
	if (indice == 0)
	{
		close(f->outfile);
		exit(1);
	}
	if (indice == 1)
	{
		close(f->infile);
		close_files(f, indice - 1);
	}
}

void	close_pipes(int i, int *fd)
{
	int j;

	j = 0;
	while (j < i)
	{
		close(fd[j]);
		j++;
	}
}

void	ft_clear1(int indice, t_d *f)
{
	if (indice == 0)
	{
		close(f->infile);
		exit(1);
	}
	if (indice == 1)
	{
		close_pipes(2, &f->pipe1);
		close_pipes(2, &f->pipe2);
		ft_clear1(indice - 1, f);
	}
}