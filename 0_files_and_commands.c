/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_files_and_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:50:45 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/15 16:06:08 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	creat_open_file(char *f1)
{
	int	fd;

	fd = open(f1, O_RDWR | O_CREAT, 0777);
	if (fd < 0)
	{
		perror("open");
		exit (1);
	}
	return (fd);
}

void	prepare_commands(char *cmd1, char *cmd2, t_d *s)
{
	char **f;
	
	f = ft_split(cmd1, ' ');
	if (!f)
		exit (1);
	else
		s->cmd1 = f;
	f = ft_split(cmd2, ' ');
	if (!f)
	{
		split_free(s->cmd1, split_strlen(cmd1, ' ', 0));
		exit (1);
	}
	else
		s->cmd2 = f;
	s->l_cmd1 = split_strlen(cmd1, ' ', 0);
	s->l_cmd2 = split_strlen(cmd2, ' ', 0);
}