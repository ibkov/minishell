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

int search_binary(__unused char *command, char **envp, t_main *main)
{
    char *path;
    char **bin_list;
    int i = 1;
    DIR *dir;

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