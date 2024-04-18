/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:45:24 by anqabbal          #+#    #+#             */
/*   Updated: 2024/04/17 15:32:36 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	nl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] &&  str[i] != '\n')
		i++;
	return (i);
}

void read_from_her_doc(int *fd, char *limiter, t_d *f)
{
	char *res;

	while(1)
	{
		res = get_next_line(STDIN_FILENO);
		if (!res)
			break;
		else if (!ft_strncmp(res, limiter, ft_strlen(limiter)))
		{
			free(res);
			break;
		}
		else
			write(*fd, res, nl_strlen(res) + 1);
		free(res);
	}
	/*before return close hte files and pipes */
}