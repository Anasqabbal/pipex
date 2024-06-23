/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:18:09 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/21 15:53:13 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char  *e_m(char *msg, char *str, int ret)
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

void	ft_clear(t_d *f)
{
	close(f->fd1);
	close(f->fd2);
}

char *check_acceess(char *cmd, char *path)
{
    char *res1;

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


char    *jib_lpath(char *cmd, char *path)
{
    char **res;
    char *res1;
    int i;

    i = 0;    
    res = ft_split(path, ':');
    if (!res)
        return (0);
    if (!res[0])
        return (split_free(res, 1) , ft_strdup("/bin/"));
    while (res[i])
    {
        res1 = check_acceess(cmd, ft_strchr(res[i], '/'));
        if (res1)
            return (split_free(res, split_strlen(path, ':', 0)), res1);
        i++;
    }
    return (split_free(res, split_strlen(path, ':', 0)), NULL);
}

char *check__path(char *cmd, char **env)
{
    char *path;

    if (ft_strchr(cmd, '/'))
       return (cmd);
    else
    {
        int i;

        i = 0;
        while (env[i])
        {
            path = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
            if (path)
            {
                path = jib_lpath(cmd, env[i]);
                if (!path)
                    return (e_m("command not found", cmd, 1));
                else
                    return (path);
            }            
            i++;
        }
    }
	return (path);
}

