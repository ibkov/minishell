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
#include <readline/readline.h>
#include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

extern t_sig g_sig;

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_main
{
    char    *base_command;
    char    **command;
    char    *unix_path;
    char    **envp;
    int     exit;
    int     quit;
}                   t_main;
void    parse(__unused t_main *main, char *command);
char    *del_spaces(char *str);
char    *create_path(char **components, int len);
int     count_len(char **argv);
void    change_envp(char **envp, char *variable, char *value);
void    init_envp(t_main *main, char **envp);
void    export(t_main *main, char *variable, char *value);
void    free_envp(t_main *main);
void	redirect(t_main *main);

void    cd(t_main *main);

void	sig_int(int code);
void	sig_quit(int code);
void	sig_init(void);
#endif