#include "minishell.h"

int arg_in_env(t_main *main, char *str, int j){
    char **temp_str;

    while(main->envp[j]){
        temp_str = ft_split(main->envp[j], '=');
        if (ft_strncmp(str, temp_str[0], ft_strlen(temp_str[0])) == 0)
            return (1);
        j++;
    }
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

void create_env(t_main *main, int i, int j, int k)
{
    char **tmp_env;
    char **temp_str;

    if(arg_in_env(main, main->tokens[i], 0)){
        tmp_env = (char **)malloc((count_env_args(main, 0)) * sizeof(char *));
            while(main->envp[j] != NULL)
            {
                temp_str = ft_split(main->envp[j], '=');
                if (ft_strncmp(main->tokens[i], temp_str[0], ft_strlen(temp_str[0])) != 0)
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
    if (main->tokens[1] == 0)
        printf("%s", "unset: not enough arguments\n");
    else
    {
        while (main->tokens[i]){
            if (ft_isdigit(main->tokens[i][0]))
            {
                printf("unset: %s: invalid parameter name\n", main->tokens[i]);
                return ;
            }
            create_env(main, i, 0, 0);
            i++;
        }
    }
}



// void create_new_env(t_main *main, char **tmp_argv, int i, int j)
// {
//     char **temp_str;

//     while (main->tokens[i])
//     {
//         j = 0;
//         while(main->envp[j]){
//             temp_str = ft_split(main->envp[j], '=');
//             if (ft_strncmp(main->tokens[i], temp_str[0], ft_strlen(temp_str[0])) == 0)
//                 count++;
//             j++;
//         }
//         i++;
//     }   
//     return (count);
// }

// int check_invalid(char **lst_argv, int i, int check){
//     if (ft_isdigit(lst_argv[++i][0]))
//         return (1);
//     while (lst_argv[i] && check)
//     {
//         if (ft_isdigit(lst_argv[i][0]))
//             check = 0;
//         i++;
//     }
//     if (check)
//         return (0);
//     return (i - 1);
// }

// void sh_unset(t_main *main)
// {
//     int i;
//     int j;
//     char **lst_argv;
//     char **temp_str;
//     char **temp_argv;

//     i = 0;
//     j = 0;
//     lst_argv = main->tokens;
//     printf("%s", lst_argv[1]);
//     if (lst_argv[1] == 0)
//         printf("%s", "unset: not enough arguments\n");
//     else if (check_invalid(lst_argv, 0, 1))
//         printf("unset: %s: invalid parameter name\n", lst_argv[check_invalid(lst_argv, 0, 1)]);
//     else
//     {
//         while(main->envp[i] != 0)
//             i++;
//         temp_argv = (char **)malloc((i) * sizeof(char *));
//         i = 0;
//         while(main->envp[i] != NULL)
//         {
//             temp_str = ft_split(main->envp[i], '=');
//             if (ft_strncmp(lst_argv[1], temp_str[0], ft_strlen(temp_str[0])) != 0)
//             {
//                 temp_argv[j] = ft_strdup(main->envp[i]);
//                 j++;
//             }
//             free_argv(temp_str);
//             i++;
//         }
//         temp_argv[j] = NULL;
//         free_argv(main->envp);
//         main->envp = temp_argv;
//     }
// }