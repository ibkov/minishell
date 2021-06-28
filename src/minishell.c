#include <stdio.h>
#include "minishell.h"

t_sig	g_sig;

int executor(__unused t_main *main, char **envp)
{
	char *dir = NULL;
	int i = 0;
	
	main->unix_path = ft_strjoin("/bin/", main->command[0]); //malloc √
	if (ft_strncmp(&main->base_command[0],"export", 6) == 0)
	{
		export(main, "TEST=", "test");
	}
	else if (ft_strncmp(&main->base_command[0], "unset", 5) == 0)
	{
		sh_unset(main);
	}
	else if (ft_strncmp(&main->base_command[0],"env", 3) == 0)
	{
		while (envp[i] != NULL)
		{
			printf("%s\n", envp[i++]);
		}
	}
	else if (ft_strncmp(&main->base_command[0],"cd", 2) == 0)
	{
		dir = getcwd(dir, 100);
		if (ft_strncmp(main->command[1],"..", 2) == 0)
		{
			change_envp(envp, "OLDPWD=", dir);
			i = ft_strlen(dir);
			while(dir[i] != '/')
				i--;
			dir[i] = '\0';
		}
		chdir(dir);
		change_envp(envp, "PWD=", dir);
	}
	else if(ft_strncmp(main->command[0], "exit", 64))
	{
		g_sig.pid = fork();
		if(g_sig.pid == 0)
		{
			redirect(main);
			execve(main->unix_path, main->command, envp);
			printf("zsh: command not found: %s\n", main->command[0]);
			exit(0);
		}
		else if (g_sig.pid > 0)
			waitpid(g_sig.pid, 0, 0);
		else
			perror("Error fork\n");
	}
	else
	{
		free(main->unix_path);
		return (1);
	}
	return (0);
}

int main(int argc, __unused char **argv, char **envp)
{
	char *command;
	t_main main;
	int i;

	i = 0;
	main.exit = 0;
	command = NULL;
	if(argc == 1)
	{
		init_envp(&main, envp);
		change_envp(main.envp, "SHLVL=", "2");
		sig_init();
		while(main.exit == 0)
		{
			ft_putstr_fd("\033[0;36m\033[1m minishell ▸ \033[0m", STDERR);
			parse(&main, command);
			if(executor(&main, main.envp))
			{
				free(command);
				break;
			}
			free(command);
		}
	}
	exit (0);
}