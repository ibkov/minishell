#include "minishell.h"

void free_argv(char **argv)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (argv[i] != NULL)
        i++;
    i--;
    while(j <= i)
    {
        free(argv[i]);
        argv[i] = NULL;
        i--;
    }
}

void init_envp(t_main *main, char **envp)
{
    int i;

    i = 0;
    while(envp[i] != NULL)
		i++;
    main->envp = (char **)malloc((i + 1) * sizeof(char *));
    main->envp[i] = NULL;
    i = 0;
    while (envp[i] != NULL)
    {
        main->envp[i] = ft_strdup(envp[i]);
        i++;
    }
}

// static add_var()
// {

// }

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
    free_argv(main->envp);
    main->envp = envp;
}

void change_envp(char **envp, char *variable, char *value)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], variable, ft_strlen(variable)) == 0)
        {
            free(envp[i]);
            envp[i] = NULL;
            envp[i] = ft_strjoin(variable, value);
        }
        i++;
    }
}