#include <stdio.h>
#include "minishell.h"

t_sig	g_sig;

int is_pipe(t_token *token)
{
	while (token && token->type != END)
	{
		if (token->type == PIPE)
		{
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int first_pipe(t_token *token)
{
	while (token && token->type != END)
	{
		if (token->type == PIPE)
			return (0);
		token = token->prev;
	}
	return (1);
}

int last_pipe(t_token *token)
{
	while (token && token->type != END)
	{
		if (token->type == PIPE)
			return (0);
		token = token->next;
	}
	return (1);
}

int middle_pipe(t_token *token)
{
	if (first_pipe(token) == 0 && last_pipe(token) == 0)
	{
		return (1);
	}
	return (0);
}


int executor(__unused t_main *main, t_token *token)
{
	int fd[2];

	main->token = token;
	if (is_pipe(main->token))
	{
		pipe(fd);
		while (token && token->type != END)
		{
			if(is_bin(token->str, main))
			{
				if (first_pipe(token))
				{
					main->tokens = create_argv(main->token);
					g_sig.pid = fork();
					if(g_sig.pid == 0)
					{
						close(fd[0]);
						dup2(fd[1], 1);
						close(fd[1]);
						redirect(main);
						execve(main->unix_path, main->tokens, main->envp);
						printf("zsh: command not found: %s\n", main->tokens[0]);
						exit(1);
					}
					else if (g_sig.pid > 0)
					{
						waitpid(g_sig.pid, 0, 0);
						while (token && token->type != PIPE)
						{
							token = token->next;
						}
						token = token->next;
					}
					else
						perror("Error fork\n");
				}
				else if(last_pipe(token))
				{
					main->tokens = create_argv(token);
					g_sig.pid = fork();
					if(g_sig.pid == 0)
					{
						close(fd[1]);
						dup2(fd[0], 0);
						close(fd[0]);
						redirect(main);
						execve(main->unix_path, main->tokens, main->envp);
						printf("zsh: command not found: %s\n", main->tokens[0]);
						exit(0);
					}
					else if (g_sig.pid > 0)
					{
						waitpid(g_sig.pid, 0, 0);
						while (token && token->type != PIPE)
						{
							token = token->next;
						}
					}
					else
						perror("Error fork\n");
				}
				else
				{
					main->tokens = create_argv(token);
					g_sig.pid = fork();
					if(g_sig.pid == 0)
					{
						dup2(fd[0], 0);
						dup2(fd[1], 1);
						close(fd[1]);
						close(fd[0]);
						redirect(main);
						execve(main->unix_path, main->tokens, main->envp);
						printf("zsh: command not found: %s\n", main->tokens[0]);
						exit(0);
					}
					else if (g_sig.pid > 0)
					{
						waitpid(g_sig.pid, 0, 0);
						while (token && token->type != PIPE)
						{
							token = token->next;
						}
					}
					else
						perror("Error fork\n");
				}
			}
		}
	}
	
	// if (is_builtin(token->str))
	// {
	// 	execve_builtin(main);
	// }
	// else if(is_bin(token->str, main))
	// {
	// 	execve_bin(main);
	// 	// while (token && token->type != END)
	// 	// 	token = token->next;
	// }
	// else if(ft_strncmp(token->str, "exit", 4) == 0)
	// {
	// 	sh_exit(main);
	// 	return (1);
	// }
	close(fd[0]);
	close(fd[1]);
	return (0);
}

t_token	*next_cmd(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

int minishell(t_main *main)
{
	t_token *token;
	int i;

	token = next_cmd(main->token, NOSKIP);
	while (main->exit == 0 && token)
	{
		i = executor(main, token);
		token = next_cmd(main->token, SKIP);
	}
	return (i);
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
			if (parse(&main))
			{
				while (main.token)
				{
					if (main.token && main.token->type == END)
						main.token = main.token->next;
					if(main.token && minishell(&main))
						break;
					while(main.token && main.token->type != END)
						main.token = main.token->next;
				}
				// free_argv(main.tokens);
				// free(main.base_command);
			}
		}
	}
	free_argv(main.envp);
	return (main.exit);
}