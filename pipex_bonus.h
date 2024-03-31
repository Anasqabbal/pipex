#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "./libft/libft.h"
# include <stdio.h>

typedef struct s_d
{
	int		fd1;
	int		fd2;
	int		i;
	int		ac;
	int		p;
	int		dup;
}	t_d;

typedef struct s_p
{
	int fd[2];
}	t_p;

int		creat_open_file(char *f1, int ind);
char	*check__path(char *cmd, char **env);
void	ft_clear(t_d *f);

/* ft_clear_bonus.c */
void    clear_pipes(int **fd, int i);
int	**fds_free(int **strings, int j);

/*do_commands*/
void	first_command(char *cmd, char **env, int **fd, t_d *f);
void	last_command(char *cmd, char **env, int **fd, t_d *f);
void	mid_command(char *cmd, char **env, int **fd, t_d *f);
#endif