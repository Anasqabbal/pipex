/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:46:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/04/17 16:27:17 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


static void	open_files(int indice, t_d *f)
{
	if (indice == 0 || indice == 1)
	{
		f->outfile = open(f->av[f->ac - 1], O_RDONLY | O_CREAT, 0777);
		if (f->outfile == -1)
		{
			ft_printf("open failed with outfile\n");
			exit(1);
		}
	}
	if (indice == 1)
	{
		f->infile = open(f->av[1], O_RDONLY);
		if (f->infile == -1)
		{
			ft_printf("open failed with infile\n");
			close(f->outfile);
			exit(1);
		}
	}
}

void	complete_the_work(t_d *f, int indice)
{
	int i;

	if (indice == 1)
		i = 3;
	else if (indice == 0)
		i = 2;
	while (i < f->ac - 2)
	{
		if (pipe(f->pipe2) == -1)
		{
			ft_printf("in C_T_W the pipe2 failed\n");
			exit(1);
		}
		f->pid1 = fork();
		if (f->pid1 == -1)
		{
			ft_printf("the fork() 1 is failed \n"); // do the necessary clean up;
			exit(1);
		}
		if (f->pid1 == 0)
		{
			ft_printf("the child processe\n");
			cmd1_(f->av[i], f->env, f);
		}
		i++;
	}
	l_cmd();
}

void	with_her_doc(t_d *f)
{

	if (pipe(f->pipe1) == -1)
	{
		ft_printf("the pipe1 is failed\n");
		exit(1);
	}
	read_from_her_doc(&f->pipe1[1], f->av[2], f); 	//write into the write end of the first pipe1
	if (dup2(f->pipe1, STDIN_FILENO) == -1)
	{
		ft_printf("failed in dup2 inside with_her_doc\n"); // do the necessary clean up
		exit(1);
	}
	complete_the_work(f, 1);
}

void	without_her_doc(t_d *f)
{
	ft_printf("you should work without her_doc\n");
}

int main(int ac, char **av, char **env)
{
	t_d f;
	
	f.ac = ac;
	f.av = av;
	f.env = env;
	if (!ft_strncmp("her_doc", av[1], ft_strlen(av[1]))) /*work with herdoc*/
	{
		open_files(0, &f); /*open the files and work with it*/
		with_her_doc(&f);
		ft_printf("work with her_doc\n");
	}
	else /*work without her_doc*/
	{
		open_files(1, &f); /*open the files and work with it*/
		without_her_doc(&f);
		ft_printf("work normally\n"); 
	}
}
