/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:37:54 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/30 14:05:12 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**fds_free(int **strings, int j)
{
	while (j > 0)
	{
		free(strings[--j]);
	}
	free(strings);
	strings = NULL;
	return (strings);
}

void    clear_pipes(int **fd, int i)
{
	int j;
	int k;

	j = 0;
	while (j < i)
	{
		k = 0;
		while (k < 2)
		{
			close(fd[j][k]);
			k++;
		}
		j++;
	}
}