#include "minishell.h"

char *cd_down(char *dir, char **envp)
{
    int i;

	change_envp(envp, "OLDPWD=", dir);
	i = ft_strlen(dir);
	while(dir[i] != '/')
		i--;
	dir[i] = '\0';
    return (dir);
}

char *cd_up(char *dir, char **envp, char *str)
{
    char *tmp;

    change_envp(envp, "OLDPWD=", dir);
    tmp = dir;
    dir = ft_strjoin(tmp, "/");
    free(tmp);
    tmp = NULL;
    tmp = dir;
    dir = ft_strjoin(tmp, str);
    free(tmp);
    return (dir);
}

void cd(t_main *main)
{
    char *dir;

    dir = NULL;
    dir = getcwd(dir, 100);
	if (ft_strncmp(main->command[1],"..", 2) == 0)
	{
        dir = cd_down(dir, main->envp);
	}
    else
    {
        dir = cd_up(dir, main->envp, main->command[1]);
    }
	chdir(dir);
	change_envp(main->envp, "PWD=", dir);
	free(dir);
}