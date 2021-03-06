#include "minishell.h"

char *search_file(DIR *dir, char *file_path, char *command)
{
    struct dirent *rd;
    char *unix_path;
    char *p;

    unix_path = NULL;
    rd = readdir(dir);
    while(rd != NULL)
    {
        if (ft_strncmp(rd->d_name, command, ft_strlen(rd->d_name)) == 0)
        {
            unix_path = ft_strjoin(file_path, "/");
            p = unix_path;
            unix_path = ft_strjoin(unix_path, command);
            free(p);
            break;
        }
        rd = readdir(dir);
    }
   closedir(dir);
   return (unix_path);
}

int search_in_path(char **envp, char *command, t_main *main)
{
    char *path;
    char **bin_list;
    DIR *dir;
    int i = 0;

    i = 1;
    path = get_envi_val(envp, "PATH");
    while (*path++ != '=');
    bin_list = ft_split(path, ':');
    while (bin_list[i] != NULL)
    {
        if(!(dir = opendir(bin_list[i])))
            break;
        main->unix_path = search_file(dir, bin_list[i], command);
        if(main->unix_path != NULL)
            break;
        i++;
    }
    if (main->unix_path == NULL)
        return (0);
    return (1);
}

int search_in_command(char *command, t_main *main)
{
    DIR *dir;
    int i;

    if (*command != '/')
        return (0);
    i = ft_strlen(command);
    while (command[i] != '/')
       i--;
    command[i++] = '\0';
    if(!(dir = opendir(command)))
        return(0);
    main->unix_path = search_file(dir, command, command + i);
    if (main->unix_path == NULL)
        return (0);
    else
    {
        free(main->token->str);
        main->token->str = ft_strdup(command + i);
    }
    return (1);
}

int search_in_current_dir(char **envp, char *command, t_main *main)
{
    DIR *dir;
    char *pwd;

    pwd = get_envi_val(envp, "PWD");
    pwd = pwd + 4;
    if(!(dir = opendir(pwd)))
        return(0);
    main->unix_path = search_file(dir, pwd, command);
    if (main->unix_path == NULL)
        return (0);
    return (1);
}

int search_binary(char *command, char **envp, t_main *main)
{

    if (search_in_path(envp, command, main))
        return (1);
    if (search_in_current_dir(envp, command, main))
        return (1);
    if(search_in_command(ft_strdup(command), main))
        return (1);
    return (0);
}