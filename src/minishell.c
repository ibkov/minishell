#include <stdio.h>
#include <minishell.h>

int main()
{
    pid_t   pid;
    char    command[64];
    printf("Your command: ");
    ft_memset(command, '\0', 64);
    scanf("%s", command);
    while(ft_strncmp(command, "exit", 64))
    {
        pid = fork();
        if(pid == 0)
        {
            execlp(command, command, NULL);
            printf("Invalid command..\n");
            exit(0);
        }
        else if (pid > 0)
        {
            waitpid(pid, 0, 0);
            printf("Your command: ");
            ft_memset(command, '\0', 64);
            scanf("%s", command);
        }
        else
        {
            perror("Error fork\n");
        }
    }
    exit (0);
}