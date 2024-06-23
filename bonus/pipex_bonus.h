#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "./libft/libft.h"
# include <stdio.h>

typedef struct s_d
{
	int		fd1;
	int		fd2;
}	t_d;

int		creat_open_file(char *f1, int ind);
char	*check__path(char *cmd, char **env);
void	ft_clear(t_d *f);
int 	child_process(char *av, char **env, t_d *f);
int		last_process(char *av, char **env, t_d *f);
void 	ft_exit(char *from, char *str);
#endif