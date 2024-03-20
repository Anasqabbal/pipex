/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:01:21 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/20 15:47:04 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_paths(t_d *f)
{
	f->path1 = prepare_path(f->cmd1[0], f);
	if (!f->path1)
		ft_clear(0, 1, f);
	f->path2 = prepare_path(f->cmd2[0], f);
	if (!f->path2)
	{
		free(f->path1);
		ft_clear(0, 1, f);
	}
}
void	child_process(t_d *f, char **env, int *fds)
{
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		ft_clear(1, 1, f);
	if (dup2(f->fd1, STDOUT_FILENO) == -1)
		ft_clear(1, 1, f);
	execve(f->path1, f->cmd1, env);
	close(fds[1]);
}

void	parrent_process(t_d *f, char **env, int *fds)
{
	if (dup2(fds[0], STDOUT_FILENO) == -1)
		ft_clear(1, 1, f);
	if (dup2(f->fd2, STDOUT_FILENO) == -1)
		ft_clear(1, 1, f);
	execve(f->path2, f->cmd2, env);
	close(fds[0]);
}

void	the_pipe(t_d *f, char **env)
{
	int fds[2];
	int pid;

	get_paths(f);
	if (pipe(fds) == -1)
	{
		perror("pipe");
		ft_clear(1, 1, f);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_clear(1, 1, f);
	}
	if (pid == 0)
		child_process(f, env, fds);
	wait(NULL);
	parrent_process(f, env, fds);
	
	//ft_printf("the command line[1] == %s\n", f->cmd1[0]);
	// fd = dup2(f->fd1, 1);
	// if (fd < 0)
	// {
	// 	perror("dup");
	// 	ft_clear(0, 1, f);
	// }
	// if (execve(f->path1, f->cmd1, env) == -1)
	// 	perror("execve");
}
