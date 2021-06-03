#include <stdio.h>
#include <minishell.h>

int executor(__unused t_main *main, char *command, char **envp)
{
    pid_t   pid;
    
    char *args[] = {command, NULL};
    char *path = ft_strjoin("/bin/", command);

    if(ft_strncmp(command, "exit", 64))
    {
        pid = fork();
        if(pid == 0)
        {
            execve(path, args, envp);
            perror("execve");   
            printf("Invalid command..\n");
            exit(0);
        }
        else if (pid > 0)
        {
            waitpid(pid, 0, 0);
        }
        else
        {
            perror("Error fork\n");
        }
    }
    else
        return (1);
    return (0);
}
int main(__unused int argc, __unused char **argv, __unused char **envp)
{
    char *command;
    t_main main;

    if(argc == 1)
    {
        while(1)
        {
            ft_putstr_fd("sh>", 1);
            get_next_line(1, &command);
            // parser(line, &main);
            if(executor(&main, command, envp))
            {
                free(command);
                break;
            }
            free(command);
        }
    }
    else
    {
        int loop = 0;

        while(loop <= argc)
        {
            printf("%s\n", argv[loop]);
            loop++;
        }

    }
    exit (0);
}