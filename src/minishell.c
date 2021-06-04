#include <stdio.h>
#include <minishell.h>

int executor(__unused t_main *main, char **envp)
{
    pid_t   pid;
    
    char *args[] = {main->base_command, main->mod_command,NULL};
    printf("base = %s\n mod = %s\n", main->base_command, main->mod_command);
    char *path = ft_strjoin("/bin/", main->base_command);

    if(ft_strncmp(main->base_command, "exit", 64))
    {
        pid = fork();
        if(pid == 0)
        {
            execve(path, args, envp);
            perror("zsh");   
            printf("zsh: command not found: %s\n", main->base_command);
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
            parse(&main, command);
            if(executor(&main, envp))
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