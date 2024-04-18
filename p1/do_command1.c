/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:02:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/04/17 16:26:39 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	do_command(char *cmd, char **env, t_d *f)
{
	char *path;
	char **cmd1;

	cmd1 = ft_split(cmd,  ' ');
	if (!cmd1)
	{
		/*clear the opened files*/
		exit (1);
	}
	path = check__path(cmd1[0] , env);
	if (!path)
	{
		/*clear the opened files and free the split*/
		exit (1);
	}
	if (execve(path, cmd1, env) == -1)
	{
		/*clear the opened files and free the split and the path */
		exit(1);
	}
}

void	cmd1_(char *cmd, char **env, t_d *f)
{
	if (dup2(f->pipe2[1], STDOUT_FILENO) == -1)
	{
		ft_printf("dup2 [1] failed in do_command,\n"); // you need to do the necessary clean up
	}
	do_command(cmd, env, f);
}
