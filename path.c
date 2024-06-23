/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:06:32 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/23 10:43:51 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*e_m(char *msg, char *str, int ret)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	if (ret == 1)
		return (NULL);
	return (str);
}

static char	*check_acceess(char *cmd, char *path)
{
	char	*res1;

	if (ft_strlen(ft_strrchr(path, '/')) != 2)
	{
		path = ft_strjoin(path, "/");
		if (!path)
			return (NULL);
	}
	res1 = ft_strjoin(path, cmd);
	if (!res1)
		return (NULL);
	if (access(res1, X_OK) == -1)
		return (free(res1), NULL);
	else
		return (res1);
}

static char	*jib_lpath(char *cmd, char *path)
{
	char	**res;
	char	*res1;
	int		i;

	i = 0;
	res = ft_split(ft_strchr(path, '=') + 1, ':');
	if (!res)
		return (0);
	else if (!res[0])
		return (split_free(res, 1), NULL);
	while (res[i])
	{
		res1 = check_acceess(cmd, ft_strchr(res[i], '/'));
		if (res1)
			return (split_free(res, split_strlen(path, ':', 0)), res1);
		i++;
	}
	return (split_free(res, split_strlen(path, ':', 0)), NULL);
}

static char	*jib_default_path(char *cmd)
{
	char	*path;

	path = jib_lpath(cmd, "=/bin:/usr/bin");
	if (!path)
		return (e_m("command not found", cmd, 1), NULL);
	return (path);
}

char	*check__path(char *cmd, char **env)
{
	char	*path;
	int		i;

	path = NULL;
	if (!env[0])
		return (jib_default_path(cmd));
	else
	{
		if (cmd && ft_strchr(cmd, '/'))
			return (ft_strdup(cmd));
		i = -1;
		while (env[++i])
		{
			path = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
			if (path)
			{
				path = jib_lpath(cmd, env[i]);
				if (!path)
					return (e_m("command not found", cmd, 1), NULL);
				else
					return (path);
			}
		}
	}
	return (e_m("command not found", cmd, 1), NULL);
}
