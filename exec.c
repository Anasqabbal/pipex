/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:50:00 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/22 17:14:19 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_w_exit(char *path, char **s, t_p *e, int ind)
{
	int	i;

	close_files(e);
	if (path)
		free(path);
	if (s)
	{
		i = -1;
		while (s[++i])
			free(s[i]);
		free(s);
	}
	exit (ind);
}

static char	which_one(char *s)
{
	if (ft_strchr(s, '\''))
		return ('\'');
	else
		return (' ');
}

static int	correct_it(char *s, char ***s1)
{
	int		i;
	char	**res;
	int		len;
	char	*res2;

	i = -1;
	res = *s1;
	if (ft_strchr(s, '\''))
	{
		if (ft_strchr(res[0], ' '))
		{
			len = ft_strlen(res[0]);
			res2 = malloc(sizeof(char) * len);
			if (!res2)
				return (1);
			while (++i < len - 1)
				res2[i] = res[0][i];
			res2[len - 1] = '\0';
			free(res[0]);
			*((*s1) + 0) = res2;
		}
	}
	return (0);
}

void	do_command(char *cmd, char **env, t_p *e)
{
	char	*path;
	char	**cmd1;

	cmd1 = ft_split(cmd, which_one(cmd));
	if (!cmd1)
		clear_w_exit(NULL, NULL, e, 1);
	if (ft_strchr(cmd, '\''))
	{
		if (correct_it(cmd, &cmd1))
			clear_w_exit(NULL, cmd1, e, 1);
	}
	path = check__path(cmd1[0], env);
	if (!path)
		clear_w_exit(path, cmd1, e, 1);
	if (execve(path, cmd1, env) == -1)
	{
		ft_putstr_fd("pipex : no such file or directory", 2);
		ft_putendl_fd(cmd1[0], 2);
		clear_w_exit(path, cmd1, e, 1);
	}
}
