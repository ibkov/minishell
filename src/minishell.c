#include <stdio.h>
#include "minishell.h"

t_sig	g_sig;

int executor(__unused t_main *main, char **envp)
{
	main->unix_path = ft_strjoin("/bin/", main->tokens[0]);
	if (ft_strncmp(&main->base_command[0],"export", 6) == 0)
	{
		sh_export(main);
	}
	else if (ft_strncmp(&main->base_command[0], "unset", 5) == 0)
	{
		sh_unset(main);
	}
	else if (ft_strncmp(&main->base_command[0],"env", 3) == 0)
	{
		sh_env(main->envp);
	}
	else if (ft_strncmp(&main->base_command[0],"cd", 2) == 0)
	{
		cd(main);
	}
	else if(ft_strncmp(main->tokens[0], "exit", 64))
	{
		g_sig.pid = fork();
		if(g_sig.pid == 0)
		{
			execve(main->unix_path, main->tokens, envp);
			printf("zsh: command not found: %s\n", main->tokens[0]);
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
	free(main->unix_path);
	return (0);
}

int main(int argc, __unused char **argv, char **envp)
{
	t_main main;
	int i;

	i = 0;
	main.exit = 0;
	if(argc == 1)
	{
		init_envp(&main, envp);
		sig_init();
		change_envp(main.envp, "SHLVL=", "2");
		while(main.exit == 0)
		{
			parse(&main);
			if(executor(&main, main.envp))
			{
				break;
			}
			free(main.base_command);
			free_argv(main.tokens);
		}
	}
	free_argv(main.envp);
	exit (0);
}