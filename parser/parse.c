#include "minishell.h"

void    parse(__unused t_main *main, __unused char *command)
{
    char **commands;
    int i = 0;

    command = del_spaces(command);
    commands = ft_split(command, ' '); // malloc
    while (commands[i] != NULL)
    {
        commands[i] = del_spaces(commands[i]);
        i++;
    }
    main->base_command = commands[0];
    main->mod_command = commands[1];
}