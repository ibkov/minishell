#include <stdio.h>
#include "minishell.h"

t_sig	g_sig;

int executor(__unused t_main *main, t_token *token)
{
	if (is_builtin(token->str))
	{
		execve_builtin(main);
	}
	else if(is_bin(token->str, main))
	{
		execve_bin(main);
		while (token && token->type != END)
			token = token->next;
	}
	else if(ft_strncmp(token->str, "exit", 4) == 0)
	{
		sh_exit(main);
		return (1);
	}
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
					if (main.token)
						main.token = main.token->next;
				}
				// free_argv(main.tokens);
				// free(main.base_command);
			}
		}
	}
	free_argv(main.envp);
	return (0);
}