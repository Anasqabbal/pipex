#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <stdio.h>

typedef struct s_d
{
	int		fd1;
	int		fd2;
}	t_d;

typedef struct s_p
{
	int fd[2];
}	t_p;

int		creat_open_file(char *f1, int ind);
char	*check__path(char *cmd, char **env);
void	ft_clear(t_d *f);
#endif