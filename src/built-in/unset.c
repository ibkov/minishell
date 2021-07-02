#include "minishell.h"

int arg_in_env(t_main *main, char *str, int j)
{
    char **temp_str;

    while(main->envp[j])
    {
        temp_str = ft_split(main->envp[j], '=');
        if (ft_strncmp(str, temp_str[0], ft_strlen(temp_str[0])) == 0)
            return (1);
        j++;
    }
    free_argv(temp_str);
    return (0);
 
}

int count_env_args(t_main *main, int i)
{
    while(main->envp[i])
    {
        i++;
    }
    return (i);
}

void create_env(t_main *main, int j, int k)
{
    char **tmp_env;
    char **temp_str;

    if(arg_in_env(main, main->token->str, 0))
    {
        tmp_env = (char **)malloc((count_env_args(main, 0)) * sizeof(char *));
            while(main->envp[j] != NULL)
            {
                temp_str = ft_split(main->envp[j], '=');
                if (ft_strncmp(main->token->str, temp_str[0], ft_strlen(temp_str[0])) != 0)
                {
                    tmp_env[k] = ft_strdup(main->envp[j]);
                    k++;
                }
                free_argv(temp_str);
                j++;
            }
        tmp_env[k] = NULL;
        free_argv(main->envp);
        main->envp = tmp_env;
    }
}

void sh_unset(t_main *main)
{
    int i;

    i = 1;
    if (!main->token->next)
        printf("%s", "unset: not enough arguments\n");
    else
    {
        while (main->token){
            if (ft_isdigit(main->token->str[0]))
            {
                printf("unset: %s: invalid parameter name\n", main->token->str);
                return ;
            }
            create_env(main, 0, 0);
            main->token = main->token->next;
        }
    }
}
