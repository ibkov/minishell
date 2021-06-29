#include "minishell.h"

void	redirect(t_main *main)
{
	int fd;

	if(main->redirect.amount == 1)
	{
		fd = open(main->redirect.redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0664);
		dup2(fd, 1);
	}
	else if(main->redirect.amount == 2)
	{
		fd = open(main->redirect.redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
		dup2(fd, 1);
	}
	free(main->redirect.redirect_file);
	main->redirect.redirect_file = NULL;
}