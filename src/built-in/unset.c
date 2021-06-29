#include "minishell.h"

void sh_unset(t_main *main)
{
    int i;
    int j;
    char **lst_argv;
    char **temp_str;
    char **temp_argv;

    i = 0;
    j = 0;
    lst_argv = main->tokens;
    if (lst_argv[1] == 0)
        printf("%s", "unset: not enough arguments\n");
    else if (ft_isdigit(lst_argv[1][0]))
        printf("unset: %s: invalid parameter name\n", lst_argv[1]);
    else
    {
        while(main->envp[i] != 0)
            i++;
        temp_argv = (char **)malloc((i) * sizeof(char *));
        i = 0;
        while(main->envp[i] != NULL)
        {
            temp_str = ft_split(main->envp[i], '=');
            if (ft_strncmp(lst_argv[1], temp_str[0], ft_strlen(temp_str[0])) != 0)
            {
                temp_argv[j] = ft_strdup(main->envp[i]);
                j++;
            }
            free_argv(temp_str);
            i++;
        }
        temp_argv[j] = NULL;
        free_argv(main->envp);
        main->envp = temp_argv;
    }
}