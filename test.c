/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:28:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/20 13:56:44 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av)
{	
	char *rd;

	int pid;

	/* creat two files of pipe */
	if (pid < 0)
		ft_printf("the fork failed\n");
	int fd[2];
	if (pipe(fd) < 0)
	{
		ft_printf("there is an error in pipe\n");
		return (1);
	}
	// creat child process 
	pid = fork();
	
	if ( pid == 0)
	{
		char *s = "this message from child";
		// you are inside the child process
		close(fd[0]);  //close the read file
		write(fd[1], s, ft_strlen(s));
	}
	else
	{
		char *buffer[324];  //creat a buffer
		close(fd[1]); //close the write file in parent process
		if (!read(fd[0], buffer, sizeof(buffer)))
			perror("read");
		else
			ft_printf("buffer == %s\n", buffer);
	}

	
}