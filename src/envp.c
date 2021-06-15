#include "minishell.h"

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