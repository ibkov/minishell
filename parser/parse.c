#include "minishell.h"

void    parse(__unused t_main *main)
{
    int argc;
    int i;

    i = 0;
    argc = 0;
    signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
    main->cmd = readline("\033[0;36m\033[1m minishell ▸ \033[0m");
    if (main->cmd == NULL && (main->exit = 1))
    {
        ft_putendl_fd("exit", STDERR);
    }
    add_history(main->cmd);
    main->base_command = ft_strdup(main->cmd); //malloc
    main->command = ft_split(main->cmd, ' ');
    free(main->cmd);
}