/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:25:36 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/21 15:50:57 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void 	ft_exit(char *from, char *str)
{
	(void) str;
	if (from)
		perror(from);
	exit(1);
}

static char which_one(char *s)
{
    if (ft_strchr(s, '\''))
        return ('\'');
    else
        return (' ');
}

static int correct_it(char *s, char ***s1)
{
    int     i;
    char    **res;
    int     len;
    char    *res2;

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
            while(++i < len - 1)
                res2[i] = res[0][i];
            res2[len - 1] = '\0';
            free(res[0]);
            *((*s1) + 0) = res2;
        }
    }
    return (0);
}

static void	do_command(char *cmd, char **env, t_d *f)
{
	char *path;
	char **cmd1;
	(void) f;

	cmd1 = ft_split(cmd,  which_one(cmd));
	if (!cmd1)
		ft_exit(NULL, NULL); //clear f
	if (ft_strchr(cmd, '\''))
	{
		if (correct_it(cmd, &cmd1))
			ft_exit(NULL, NULL);
	}
	path = check__path(cmd1[0] , env);
	if (!path)
	{
		ft_exit(NULL, NULL); //clear f
	}
	if (execve(path, cmd1, env) == -1)
		ft_exit("execve", NULL); //clear f
}

int 	child_process(char *av, char **env, t_d *f)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		ft_exit("pipe", NULL);
	pid = fork();
	if (pid == -1)
		ft_exit("fork", NULL);
	if (pid == 0)
	{
		close(fd[0]); //f[0] read-end;
		dup2(fd[1], STDOUT_FILENO); //f[1] write-end;
		close(fd[1]);
		do_command(av, env, f);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		return (0);
	}
	return(0);
}

int		last_process(char *av, char **env, t_d *f)
{
	int	pid;
	int status;

	pid = fork();
	if (pid < 0)
		ft_exit("fork", NULL);
	if (pid == 0)
	{
		if (dup2(f->fd2, STDOUT_FILENO) < 0)
			ft_exit("dup2", NULL);
		do_command(av, env, f);
	}
	else
	{
		close(0);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}
