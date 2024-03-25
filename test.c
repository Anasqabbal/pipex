#include "pipex.h"

void	do_child_process(int *fd, char **av, char **env)
{
	int infile;
	char **split;

	split = ft_split(av[2], ' ');
	infile = open(av[1], O_RDWR);
	if (infile == -1)
	{
		perror("open :");
		exit(1);
	}

	close(fd[0]); // close the reading

	if (dup2(infile, STDIN_FILENO) == -1)
		ft_printf("error with fd[1]\n");
	
	close(infile); //close infile

	if (dup2(fd[1], STDOUT_FILENO) == -1) // writing pipe acts as outputfile (1)
		ft_printf("error with fd[1]\n");
	
	close(fd[1]); //after duplicating close the reading

	if (execve("/bin/ls", split, env) == -1) //execute the command
		exit(1);
}

void	do_parent_process(int *fd, char **av, char **env)
{
	int outfile;
	char **split;

	split = ft_split(av[3], ' ');

	outfile = open(av[4], O_RDWR | O_CREAT, 0777);
	if (outfile == -1)
		perror(" outfile open :");

	close(fd[1]) ;// close the writing pipe;

	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_printf("error with fd[1]\n");
	close(fd[0]); //close the reading pipe;


	if (dup2(outfile, STDOUT_FILENO) == -1)
		ft_printf("error with fd[1]\n");
	close(outfile); //close the outfile 


	if (execve("/bin/ls", split, env) == -1) //execute the command
		exit(1);
}

int	main(int ac, char **av, char **env)
{
	int fd[2];
	int pid;

	if (pipe(fd) == -1)
		exit(1);

	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}

	if (!pid)
		do_child_process(fd, av, env);
	else
		do_parent_process(fd, av, env);
}
