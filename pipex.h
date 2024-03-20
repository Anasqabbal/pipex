#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <stdio.h>

typedef struct s_d
{
	int		fd1;
	int		fd2;
	char 	**cmd1;
	char 	**cmd2;
	int		l_cmd1;
	int		l_cmd2;
	char	*path1;
	char	*path2;
}	t_d;

typedef struct s_p
{
	int fd[2];
}	t_p;

int		creat_open_file(char *f1);
void	prepare_commands(char *cmd1, char *cmd2, t_d *s);
void	ft_clear(int indice, int e_indice, t_d *f);
char	*prepare_path(char *str, t_d *f);
void	the_pipe(t_d *f, char **env);
#endif