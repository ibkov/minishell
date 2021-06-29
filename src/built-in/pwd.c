#include "minishell.h"

void sh_pwd(t_main *main)
{
    g_sig.pid = fork();
	if(g_sig.pid == 0)
	{
		redirect(main);
		execve(main->unix_path, main->tokens, main->envp);
		printf("zsh: command not found: |%s|\n", main->tokens[0]);
		exit(0);
	}
	else if (g_sig.pid > 0)
		waitpid(g_sig.pid, 0, 0);
	else
		perror("Error fork\n");
}