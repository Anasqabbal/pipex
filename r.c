#include "pipex.h"





void    first_command(int fd[][2], int i, char **av, char **env)
{
    (void)fd;
    (void)env;
    ft_printf("your first command is %s\n", av[i]);
}

void    last_command(int fd[][2], int i, char **av, char **env)
{
    (void)fd;
    (void)env;
    ft_printf("your last command is %s\n", av[i]);
}

void    midle_commands(int fd[][2], int i, char **av, char **env)
{
    (void)fd;
    (void)env;
    ft_printf("your midle command is %s\n", av[i]);
}

void    pri(int fd[][2])
{
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 2; j++)
            ft_printf("the fd[%d][%d] == %d\n", i, j, fd[i][j]);
    }
}

void	to_another_f(int **fd)
{
	exit(1);
}

void f(void){system("leaks a.out");}

int main(int ac, char **av, char **env)
{
	atexit(f);
    int j;
    int **fd;
    int pid;

    int i;

    i = 2;
	fd = creat_pipes(ac);
	fds_free(fd, ac - 3);
	to_another_f(fd);
    // while (i < ac - 1)
    // {
    //     // if (pipe(fd[i]) == -1)
    //     //     ft_printf("pipe failed\n");
    //     // pid = fork();
    //     // if (pid == -1)
    //     //     ft_printf("fork() faild\n");
    //     if (i == 2)
    //         first_command(fd, i, av, env);
    //     else if (i == ac - 2)
    //         last_command(fd, i, av, env);
    //     else
    //         midle_commands(fd, i, av, env);
    //     i++;
    // }

   // pri(fd);
}