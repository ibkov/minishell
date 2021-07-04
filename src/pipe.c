# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>

int main(void)
{
    int fd[2];
    pipe(fd);
    if(fork() == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execlp("ls", "ls", NULL);
        exit(1);
    }
    if(fork() == 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execlp("cat", "cat","-e" ,NULL);
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
}