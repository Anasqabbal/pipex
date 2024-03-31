/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:34:02 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/31 16:54:42 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	do_command(char *cmd, char **env, t_d *f)
{
	char *path;
	char **cmd1;

	cmd1 = ft_split(cmd,  ' ');
	if (!cmd1)
	{
		ft_clear(f);
		exit (1);
	}
	path = check__path(cmd1[0] , env);
	if (!path)
	{
		ft_clear(f);
		exit (1);
	}
	if (execve(path, cmd1, env) == -1)
	{
		ft_clear(f);
		exit(1);
	}
}

void	mid_command(char *cmd, char **env, int **fd, t_d *f)
{
	if (dup2(fd[f->p][0], STDIN_FILENO) == -1)
	{
		ft_printf("dup2 failed\n");
		ft_clear(f);
		exit(1);
	}
	if (dup2(fd[(f->p) + 1][1], STDOUT_FILENO) == -1)
	{
		ft_printf("dup2 failed\n");
		ft_clear(f);
		exit(1);
	}
	clear_pipes(fd, f->ac - 3);
	ft_clear(f);
	do_command(cmd, env, f);
}

void	first_command(char *cmd, char **env, int **fd, t_d *f)
{
	if (dup2(fd[f->p][1], STDOUT_FILENO) == -1)
	{
		ft_printf("dup2 failed \n");
		ft_clear(f);
		exit(1);
	}
	if (dup2(f->fd1, STDIN_FILENO) == -1)
	{
		ft_printf("dup2 failed\n");
		ft_clear(f);
		exit(1);
	}
	clear_pipes(fd, f->ac - 3);
	ft_clear(f);
	do_command(cmd, env, f);
}

void	last_command(char *cmd, char **env, int **fd, t_d *f)
{
	if (dup2(fd[f->p][0], STDIN_FILENO) == -1)
	{
		ft_printf("dup2 failed ;;;;\n");
		ft_clear(f);
		exit(1);
	}
	if (dup2(f->fd2, STDOUT_FILENO) == -1)
	{
		ft_printf("dup2 failed oooo\n");
		ft_clear(f);
		exit(1);
	}
	clear_pipes(fd, f->ac - 3);
	ft_clear(f);
	do_command(cmd, env, f);
}