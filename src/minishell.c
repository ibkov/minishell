#include <stdio.h>
#include "minishell.h"

t_sig	g_sig;

static void simple_command(t_main *main)
{
	char **p;

	if (ft_strncmp(&main->base_command[0],"/bin/", 5) == 0)
	{
		p = ft_split(&main->base_command[0], '/');
		main->tokens = ft_split(p[1], ' ');
		free_argv(p);
	}
	main->unix_path = ft_strjoin("/bin/", main->tokens[0]);
}

int		is_builtin(char *command)
{
	// if (ft_strcmp(command, "echo") == 0)
	// 	return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

void execve_builtin(t_main *main)
{
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
		sh_env(main);
	}
	else if (ft_strncmp(&main->base_command[0],"cd", 2) == 0)
	{
		cd(main);
	}
	else if (ft_strncmp(&main->base_command[0],"pwd", 3) == 0)
	{
		sh_pwd(main);
	}
}

int executor(__unused t_main *main, char **envp)
{
	simple_command(main);
	if (is_builtin(main->tokens[0]))
	{
		execve_builtin(main);
	}
	else if(ft_strncmp(&main->base_command[0], "exit", 4))
	{
		g_sig.pid = fork();
		if(g_sig.pid == 0)
		{
			redirect(main);
			execve(main->unix_path, main->tokens, envp);
			printf("zsh: command not found: |%s|\n", main->tokens[0]);
			exit(0);
		}
		else if (g_sig.pid > 0)
			waitpid(g_sig.pid, 0, 0);
		else
			perror("Error fork\n");
	}
	else
	{
		sh_exit(main);
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
			if(argv_len(main.tokens) > 0)
			{
				if(executor(&main, main.envp))
				{
					break;
				}
			}
			free_argv(main.tokens);
			free(main.base_command);
		}
	}
	free_argv(main.envp);
	return (0);
}