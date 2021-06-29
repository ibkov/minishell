#include "minishell.h"

int sh_exit(t_main *main)
{
    if (argv_len(main->tokens) == 2)
    {
        main->exit_code = ft_atoi(main->tokens[1]);
        exit(main->exit_code);
    }
    else
        return (0);
}