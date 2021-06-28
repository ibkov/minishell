#include "minishell.h"

void    parse(__unused t_main *main, __unused char *command)
{
    static char *commands[5];
    int argc;

    argc = 0;
    signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
    if (get_next_line(0, &command) == 0 && (main->exit = 1))
		ft_putendl_fd("exit", STDERR);
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