#include "minishell.h"

void free_argv(char **argv)
{
    int i;

    i = 0;
    while (argv[i] != NULL)
        i++;
    while (i >= 0)
	{
		free(argv[i]);
		i--;
	}
	free(argv);
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

void sh_env(t_main *main)
{
    char **envp;
    int i;

    envp = main->envp;
    i = 0;
    redirect(main);
    while (envp[i] != NULL)
	{
		printf("%s\n", envp[i++]);
	}
    dup2(0, 1);
}