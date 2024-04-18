#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "./libft/libft.h"
# include <stdio.h>

typedef struct s_d
{
	int		fd1;
	int		fd2;
	int		infile;
	int		outfile;
	int		pipe1[2];
	int		pipe2[2];
	int		pid1;
	int		pid2;
	char	**av;
	char	**env;
	int		ac;
}	t_d;

typedef struct s_dd
{
	int fd[2];
	int fd1[2];
}	t_dd;

int		creat_open_file(char *f1, int ind);
char	*check__path(char *cmd, char **env);
void	ft_clear(t_d *f);

/* ft_clear1_bonus.c */
void	close_pipes(int i, int *fd);


/*do_commands*/
void	cmd1_(char *cmd, char **env, t_d *f);


/*her_doc_bonus*/
void	read_from_her_doc(int *fd, char *str, t_d *f);

/*clear1_bonus*/
void	ft_clear1(int indice, t_d *f);
#endif