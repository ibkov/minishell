#include "minishell.h"

void sh_unset(t_main *main)
{
    int i;
    int j;
    char **lst_argv;
    char **temp_argv;
    int check;

    i = 0;
    j = 0;
    check = 0;
    lst_argv = ft_split(main->base_command, ' ');
    if (lst_argv[1] == 0)
        printf("%s", "unset: not enough arguments\n");
    // else if (lst_argv[1]){
    //     while (ft_isdigit(lst_argv[1][i]))
    //         i++;
    //     if (ft_isalpha(lst_argv[1][i]) && i > 0)
    //         printf("unset: %s: invalid parameter name\n", lst_argv[1]);
    //     i = 0;
    // }
    else
    {
        while(main->envp[i] != 0)
            i++;
        temp_argv = (char **)malloc((i + 1) * sizeof(char *));
        i = 0;
        while(main->envp[i] != 0){
            printf("%d  ", ft_strncmp(lst_argv[1], main->envp[i], ft_strlen(lst_argv[1])));
            printf("%s\n",  main->envp[i]);
            if (ft_strncmp(lst_argv[1], main->envp[i], ft_strlen(lst_argv[1])) != 0){
                temp_argv[j] = ft_strdup(main->envp[i]);
                j++;
            }
            i++;
        }
        temp_argv[i] = NULL;
        free(main->envp);
        main->envp = temp_argv;
    }
}