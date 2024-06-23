
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:14:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/17 15:58:42 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	creat_open_file(char *f1, int ind)
{
	int	fd;

	if (ind == 0)
		fd = open(f1, O_RDONLY);
	else if (ind == 1)
		fd = open(f1, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(f1, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(f1);
		fd = -1;
	}
	return (fd);
}

static int	open_here_doc(char *str)
{
	int		fd[2];
	char	*res;
	int		pid;

	if (pipe(fd) < 0)
		ft_exit("pipe", NULL);
	pid = fork();
	if (pid < 0)
		ft_exit("fork", NULL);
	if (pid == 0)
	{
		close(fd[0]);
		while(1)
		{
			ft__putstr_fd("> ", 1);
			res = get_next_line(0);
			if (!res || !ft_strncmp(res, str, ft_strlen(str)))
				break ;
			write(fd[1], res, (ft_strlen(res)));
			free(res);
		}
		free(res);
		exit (0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			ft_exit("dup2", NULL);
	}
	return (0);
}

static int with_here_doc(int ac, char **av, char **env, t_d *p)
{
	int		i;
	int		ret;

	i = 2;
	open_here_doc(av[2]);
	while(++i < ac - 2)
		ret = child_process(av[i], env, p);
	ret = last_process(av[i], env, p);
	return (ret);
}

static int without_here_doc(int ac, char **av, char **env, t_d *p)
{
	int		i;
	int		ret;

	i = 1;
	if (p->fd1 != - 1)
	{
		if (dup2(p->fd1, STDIN_FILENO) < 0)
			ft_exit("dup2", NULL);
	}
	else
		i = 2;
	while(++i < ac - 2)
		ret = child_process(av[i], env, p);
	ret = last_process(av[i], env, p);
	while(waitpid(-1, NULL, 0) != -1);
	return (ret);
}

int main(int ac, char **av, char **env)
{
	t_d f;
	int		ret;
	
	if (ac >= 5)
	{
		if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) && ac >= 6 && ft_strlen(av[1]) == 8)
		{
			f.fd2 = creat_open_file(av[ac - 1], 2);
			ret = with_here_doc(ac, av, env, &f);
		}
		else
		{
			f.fd1 = creat_open_file(av[1], 0);
			f.fd2 = creat_open_file(av[ac - 1], 1);
			ret = without_here_doc(ac, av, env, &f);
		}
		return (ft_clear(&f), ret);
	}
	else
		return (ft_putendl_fd("invalide arguments", 2), 1);
	
}

/* to be continuened 

	handle when you failed with open file continuee the execution with another commands


	ft_strchr segfaultt protect cmd before pass it ot it 

	good luck


*/