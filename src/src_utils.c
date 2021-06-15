#include "minishell.h"

int count_len(char **argv)
{
    int i;

    i = 0;
    while(argv[i] != NULL)
        i++;
    return (i);
}

char *create_path(char **components, int len)
{
    char *path;
    char *tmp;
    int     i;

    i = 0;
    path = "\0";
    while (components[i] != NULL && len > 0)
    {
        tmp = path;
        path = ft_strjoin(components[i], path);
        free(tmp);
        i++;
        len--;
    }
    return (path);
}