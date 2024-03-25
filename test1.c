#include "pipex.h"

void do_child_process(int *fd, char **av, char **env) {
    int infile;
    char **split;

    split = ft_split(av[2], ' ');
    infile = open(av[1], O_RDONLY); // Open for read only
    if (infile == -1) {
        perror("open infile:");
        exit(1);
    }

    close(fd[0]); // Close reading end of pipe

	int f = dup2(infile, STDIN_FILENO);
    if (f == -1) {
        perror("dup2 infile:");
        exit(1);
    }

    close(infile); // Close file descriptor after duplication

    if (dup2(fd[1], STDOUT_FILENO) == -1) {
        perror("dup2 stdout:");
        exit(1);
    }

    close(fd[1]); // Close writing end of pipe

    if (execve("/bin/ls", split, env) == -1) {
        perror("execve child:");
        exit(1);
    }
}

void do_parent_process(int *fd, char **av, char **env) {
    int outfile;
    char **split;

    split = ft_split(av[3], ' ');
    outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777); // Open for write only, creating if necessary, truncate
    if (outfile == -1) {
        perror("open outfile:");
        exit(1);
    }

    close(fd[1]); // Close writing end of pipe

    if (dup2(fd[0], STDIN_FILENO) == -1) {
        perror("dup2 stdin:");
        exit(1);
    }

    close(fd[0]); // Close reading end of pipe

    if (dup2(outfile, STDOUT_FILENO) == -1) {
        perror("dup2 outfile:");
        exit(1);
    }

    close(outfile); // Close file descriptor after duplication

    if (execve("/bin/ls", split, env) == -1) {
        perror("execve parent:");
        exit(1);
    }
}

int main(int ac, char **av, char **env) {
    int fd[2];
    int pid;

    if (ac != 5) {
        ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", av[0]);
        return 1;
    }

    if (pipe(fd) == -1) {
        perror("pipe:");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork:");
        return 1;
    }

    if (!pid) { // Child process
        do_child_process(fd, av, env);
    } else { // Parent process
        do_parent_process(fd, av, env);
    }

    return 0;
}
