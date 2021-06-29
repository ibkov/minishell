#include "minishell.h"

static int is_redirect(char *str, t_redirect *redirect)
{
    redirect->amount = 0;
    while (*str)
    {
        if (*str == '>' || *str == '<')
        {
            if (redirect->type != *str && redirect->amount != 0)
            {
                printf("Redirect error\n");
                return (-1);
            }
            else
            {
                redirect->type = *str;
                if(redirect->amount++ > 2)
                {
                    printf("Redirect error\n");
                    return (-1);
                }
            }
        }
        str++;
    }
    return (redirect->amount);
}

t_token	*new_token(void *content)
{
	t_token	*new_elem;

	new_elem = malloc(sizeof(t_token));
	if (!new_elem)
		return (0);
	new_elem->content = content;
	new_elem->next = 0;
	return (new_elem);
}

void   parse(__unused t_main *main)
{
    int i;
    char *cmd;
    char **p;

    i = 0;
    signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
    cmd = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
    if (cmd == NULL && (main->exit = 1))
    {
        ft_putendl_fd("exit", STDERR);
        exit(0);
    }
    else if (cmd != '\0')
    {
        add_history(cmd);
        main->base_command = ft_strdup(cmd); //malloc
        if (is_redirect(cmd, &main->redirect) > 0)
        {
            p = ft_split(cmd, main->redirect.type);
            main->redirect.redirect_file = del_spaces(p[1]);
            main->tokens = ft_split(p[0], ' ');
            free_argv(p);
        }
        else if(cmd != NULL)
            main->tokens = ft_split(cmd, ' ');
    }
    free(cmd);
}