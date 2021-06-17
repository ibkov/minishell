#include "minishell.h"

void export(t_main *main, char *variable, char *value)
{
    int i;
    char **envp;

    i = 0;
    while (main->envp[i] != NULL)
        i++;
    envp = (char **)malloc((i + 2) * sizeof(char *));
    envp[i + 1] = NULL;
    i = 0;
    while (main->envp[i] != NULL)
    {
        envp[i] = ft_strdup(main->envp[i]);
        i++;
    }
    envp[i] = ft_strjoin(variable, value);
    free_envp(main);
    main->envp = envp;
}