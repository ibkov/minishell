#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

typedef struct s_main
{
    char    *base_command;
    char    **command;
    char    *unix_path;
    char    **envp;
}                   t_main;
void    parse(__unused t_main *main, char *command);
void	redirect(t_main *main);
char    *del_spaces(char *str);
char    *create_path(char **components, int len);
int     count_len(char **argv);
void    change_envp(char **envp, char *variable, char *value);
void    init_envp(t_main *main, char **envp);
void    export(t_main *main, char *variable, char *value);
void    free_envp(t_main *main);
void    cd(t_main *main);
#endif