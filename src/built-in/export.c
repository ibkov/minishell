#include "minishell.h"

// static char **get_props(char *str)
// {
//     char **props;
//     char *p;

//     props = ft_split(str, '=');
//     p = props[0];
//     props[0]= ft_strjoin(props[0], "=");
//     free(p);
//     return (props);
// }

// void sh_export(t_main *main)
// {
//     int i;
//     char **envp;
//     char    **p;

//     i = 0;
//     while (main->envp[i] != NULL)
//         i++;
//     envp = (char **)malloc((i + 2) * sizeof(char *));
//     envp[i + 1] = NULL;
//     i = 0;
//     while (main->envp[i] != NULL)
//     {
//         envp[i] = ft_strdup(main->envp[i]);
//         i++;
//     }
//     p = get_props(main->token->next->str);
//     envp[i] = ft_strjoin(p[0], p[1]);
//     free_argv(p);
//     main->envp = envp;
// }


void create_env1(t_main *main)
{
    char **str;
    char **tmp_env;
    int line;
    int i;

    str = ft_split(main->token->str, '=');
    line = arg_in_env(main, str[0], 0);
    if (line != -1)
    {
        main->envp[line] = (char*)malloc(sizeof(char) * (ft_strlen(main->token->str) + 1));
        ft_strlcpy(main->envp[line], main->token->str, ft_strlen(main->token->str) + 1);
    }
    else if (ft_strchr(main->token->str, '='))
    {
        i = count_env_args(main, 0);
        tmp_env = (char **)malloc((i + 2) * sizeof(char *));
        tmp_env[i + 1] = NULL;
        i = 0;
        while (main->envp[i] != NULL)
        {
            tmp_env[i] = ft_strdup(main->envp[i]);
            i++;
        }
        tmp_env[i] = ft_strdup(main->token->str);
        main->envp = tmp_env;
    }
}

void sh_export(t_main *main)
{
    if (!main->token)
    {
        sh_env(main);
    }
    else
    {
        while (main->token && main->token->type != END){
            if (ft_isdigit(main->token->str[0]))
            {
                printf("export: not an identifier: %s\n", main->token->str);
                return ;
            }
            else if (main->token->type == ARG)
            {
                create_env1(main);
            }
            main->token = main->token->next;
        }
    }


}