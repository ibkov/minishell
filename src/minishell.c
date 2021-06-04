#include <stdio.h>
#include <minishell.h>

void	redirect(t_main *main)
{
	int redirect_flag = 0;
	char *redirect_file = NULL;
	int i = 0;
	int id;

	while(main->command[i])
	{
		if (ft_strncmp(main->command[i], ">", 1) == 0)
		{
			if (ft_strncmp(main->command[i], ">>", 2) == 0)
			{
				redirect_flag++;
			}
			redirect_flag++;
			id = i;
			main->command[i] = NULL;
		}
		i++;
	}
	if (redirect_flag > 0)
		redirect_file = main->command[id + 1];

	if(redirect_flag == 1)
	{
		int fd = open(redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0664);
		dup2(fd, 1);
		// Перенаправляем стандартный вывод в файл
		// это перенаправление перезаписи, открыто в режиме перезаписи O_TRUNC
	}
	else if(redirect_flag == 2)
	{
		int fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
		dup2(fd, 1);
		//это дополнительное перенаправление, открытое в режиме добавления O_APPEND
	}
}

int executor(__unused t_main *main, char **envp)
{
	pid_t	pid;
	char	*path;
	
	path = ft_strjoin("/bin/", main->command[0]); //malloc √
	if(ft_strncmp(main->command[0], "exit", 64))
	{
		pid = fork();
		if(pid == 0)
		{
			redirect(main);
			execve(path, main->command, envp);
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
		free(path);
		return (1);
	}
	return (0);
}

int main(__unused int argc, __unused char **argv, __unused char **envp)
{
	char *command;
	t_main main;

	if(argc == 1)
	{
		while(1)
		{
			ft_putstr_fd("sh>", 1);
			get_next_line(1, &command);
			parse(&main, command);
			if(executor(&main, envp))
			{
				free(command);
				break;
			}
			free(command);
		}
	}
	exit (0);
}