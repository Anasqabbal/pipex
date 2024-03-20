#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>

int main() {
  int fd[2]; // Array to store file descriptors for the pipe
  pid_t pid;

  if (pipe(fd) == -1) {
    perror("pipe");
    exit(1);
  }

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0)
{
    // Child process (reads from the pipe)
    close(fd[1]); // Close write end
    char buffer[100];
    read(fd[0], buffer, sizeof(buffer)); // Read from pipe
    printf("Child process (pid=%d) received: %s\n", getpid(), buffer);
  }
  else
  {
    // Parent process (writes to the pipe)
    close(fd[0]); // Close read end
    const char* message = "Hello from parent process!";
    write(fd[1], message, strlen(message) + 1); // Write to pipe
  }
  return 0;
}