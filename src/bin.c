#include "minishell.h"

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
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
	if (ft_strncmp(main->token->str,"export", 6) == 0)
		sh_export(main);
	else if (ft_strncmp(main->token->str, "unset", 5) == 0)
		sh_unset(main);
	else if (ft_strncmp(main->token->str,"env", 3) == 0)
		sh_env(main);
	else if (ft_strncmp(main->token->str,"cd", 2) == 0)
		cd(main);
	else if (ft_strncmp(main->token->str,"pwd", 3) == 0)
		sh_pwd(main);
}

int		is_bin(char *command, t_main *main)
{
	if (search_binary(command, main->envp, main))
		return (1);
	return (0);
}

void execve_bin(t_main *main)
{
	int fd[2];

	pipe(fd);

	main->tokens = create_argv(main->token);
	g_sig.pid = fork();
	if(g_sig.pid == 0)
	{
		// dup2(fd[1], 1);
		// close(fd[0]);
		redirect(main);
		execve(main->unix_path, main->tokens, main->envp);
		printf("zsh: command not found: %s\n", main->tokens[0]);
		exit(0);
	}
	else if (g_sig.pid > 0)
	{
		// char buf;
		// close(fd[1]);
		// while (read(fd[0], &buf, 1) > 0)
		// 	write(1, &buf, 1);
		waitpid(g_sig.pid, 0, 0);
	}
	else
		perror("Error fork\n");
	
}