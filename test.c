#include "pipex_bonus.h"
//creat pipes

void	creat_pipes(int ***p)
{

}



int main(int ac, char **av, char **env)
{
	int		fd[ac - 3][2];
	int		pid;
	int		i;

	i = 0;
	while (i < ac - 3)
	{
		if (pipe(fd[i]) == -1)
			return(ft_printf("pipe failed\n"), 0);
		pid = fork();
		if (pid == -1)
			return(ft_printf("fork failed\n"), 0);		
	}
	pid = fork();
	if (pid == 0)
		ft_printf("this is the child \n");
	else if (pid != 0)
		ft_printf("this is not the child\n");
	int pid2 = fork();
	if (pid2 != 0)
		ft_printf("the parent of the second fork()\n");
}