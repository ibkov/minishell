#include "minishell.h"

void    parse(__unused t_main *main, __unused char *command)
{
    static char *commands[5];
    int argc;

    argc = 0;
    main->base_command = ft_strdup(command); //malloc
    while (*command != '\0')
    {
        if (*command != ' ')
        {
            commands[argc++] = command;
            while (*command != '\0' && *command != ' ')
                command++;
            *command = '\0';
        }
        command++;
    }
    commands[argc] = NULL;
    main->command = commands;
}