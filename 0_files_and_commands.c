/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_files_and_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:50:45 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/18 16:07:49 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_clear(int indice, int e_indice, t_d *f)
{
	if (indice >= 0)
	{
		split_free(f->cmd1, f->l_cmd1);
		split_free(f->cmd2, f->l_cmd2);
	}
	exit(e_indice);
}

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
	if (!f || !f[0])
		exit (1);
	else
		s->cmd1 = f;
	f = ft_split(cmd2, ' ');
	if (!f || !f[0])
	{
		split_free(s->cmd1, split_strlen(cmd1, ' ', 0));
		exit (1);
	}
	else
		s->cmd2 = f;
	ft_printf("the command n1 == %s\n", s->cmd1[0]);
	ft_printf("the command n2 == %s\n", s->cmd2[0]);
	s->l_cmd1 = split_strlen(cmd1, ' ', 0);
	s->l_cmd2 = split_strlen(cmd2, ' ', 0);
}

int	it_is_valid_(char *str, t_d *f, char **res)
{
	char	*res1;
	char	*res2;

	res = ft_split(str, '/');
	if (!res)
		ft_clear(0, 1, f);
	res1 = ft_strjoin("/", res[0]);
	if (!res1)
	{
		split_free(res, split_strlen(str, '/', 0));
		ft_clear(0, 1, f);
	}
	split_free(res, split_strlen(str, '/', 0));
	res2 = ft_strjoin(res1, "/");
	if (!res2)
	{
		free(res1);
		ft_clear(0, 1, f);
	}
	free(res1);
	ft_printf("res2 == %s", res2);
	if (!ft_strncmp("/bin/", res2, 5))
		return (free(res2), 1);
	else
		return (free(res2), 0);
}

void	prepare_path(char *str, t_d *f)
{
	int	len;
	(void) f;

	len = split_strlen(str, '/', 0);
	ft_printf("the len is %d\n", len);
	if (len == 1)
	{
		f->path = ft_strjoin("/bin/", str);
		if (!f->path)
			ft_clear(0, 1, f);
	}
	else if (len == 2)
	{
		if(!it_is_valid_(str, f, NULL))
			ft_clear(0, 1, f);
		f->path = str;
	}
	else
		ft_clear(0, 1, f);
}
