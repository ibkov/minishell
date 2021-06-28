#include "minishell.h"

static char *cd_down(char *dir, char **envp)
{
    int i;

    change_envp(envp, "OLDPWD=", dir);
	i = ft_strlen(dir);
	while(dir[i] != '/')
		i--;
	dir[i] = '\0';
    return (dir);
}

static char *cd_rel(char *dir, char **envp, char *val)
{
    char *tmp;

    change_envp(envp, "OLDPWD=", dir);
    tmp = val;
    val = ft_strjoin("/", val);
    free(tmp);
    tmp = NULL;
    tmp = dir;
    dir = ft_strjoin(dir, val);
    free(tmp);
    free(val);
    return (dir);
}

void    cd(t_main *main)
{   
    char *dir;

    dir = NULL;
    dir = getcwd(dir, 100);
	if (ft_strncmp(main->command[1],"..", 2) == 0)
	{
        dir = cd_down(dir, main->envp);
	}
    else if(ft_strncmp(main->command[1], dir, ft_strlen(dir)) == 0)
    {
        change_envp(main->envp, "OLDPWD=", dir);
        dir = ft_strdup(main->command[1]);
    }
    else 
    {
        dir = cd_rel(dir, main->envp, main->command[1]);
    }
	chdir(dir);
	change_envp(main->envp, "PWD=", dir);
    free(dir);
}