#include <stdio.h>
#include "minishell.h"

int executor(__unused t_main *main, char **envp)
{
	pid_t	pid;
	int i = 0;
	
	main->unix_path = ft_strjoin("/bin/", main->command[0]);
	if (ft_strncmp(&main->base_command[0],"export", 6) == 0)
	{
		export(main,"TEST=", "test");
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
		cd(main);
	}
	else if(ft_strncmp(main->command[0], "exit", 64))
	{
		pid = fork();
		if(pid == 0)
		{
			redirect(main);
			execve(main->unix_path, main->command, envp);
			perror("zsh");   
			printf("zsh: command not found: %s\n", main->command[0]);
			exit(0);
		}
		else if (pid > 0)
			waitpid(pid, 0, 0);
		else
			perror("Error fork\n");
	}
	else
	{
		return (1);
	}
	return (0);
}

int main(__unused int argc, __unused char **argv, __unused char **envp)
{
	char *command;
	t_main main;
	int i;

	i = 0;
	if(argc == 1)
	{
		init_envp(&main, envp);
		while(1)
		{
			ft_putstr_fd("sh>", 1);
			get_next_line(1, &command);
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