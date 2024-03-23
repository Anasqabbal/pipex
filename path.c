/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:06:32 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/23 11:44:23 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *check_acceess(char *cmd, char *path)
{
    char *res1;

    if (ft_strlen(ft_strrchr(path, '/')) != 2) /* checki wach lpath f lakhr dyalo / wla la ila makantch zidha 3la lpath */
    {
        //ft_printf("your should join / at the end\n");
        path = ft_strjoin(path, "/"); /* zid '/' 3la lpath */
        if (!path)
            return (NULL);
    }
    res1 = ft_strjoin(path, cmd); /* jma3 lpath w lcommand w checki laccess */
    if (!res1)
        return (NULL);
    if (access(res1, X_OK) == -1)
    {
        //ft_printf("-- %s --\n", res1);
        return (free(res1), NULL);
    }
    else
        return (res1); /* returni lpath */
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
                    return (NULL);
                else
                    return (path);
            }            
            i++;
        }
    }
	return (path);
}