/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:11:06 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/22 18:14:35 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <stdio.h>
# include <string.h>

typedef struct s_p
{
	int		pid;
	int		fd[2];
	int		fd0;
	int		fd1;
	char	**env;
	char	**av;
	int		ac;
}	t_p;

int		creat_open_file(char *f1, int ind);
char	*check__path(char *cmd, char **env);
void	close_files(t_p *e);
void	do_command(char *cmd, char **env, t_p *e);
#endif