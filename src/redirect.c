#include "minishell.h"

void	redirect(t_redirect *redirect, char *redirect_file)
{
	int fd;

	if(redirect->amount == 1)
	{
		fd = open(redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0664);
		dup2(fd, 1);
		// Перенаправляем стандартный вывод в файл
		// это перенаправление перезаписи, открыто в режиме перезаписи O_TRUNC
	}
	else if(redirect->amount == 2)
	{
		fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
		dup2(fd, 1);
		//это дополнительное перенаправление, открытое в режиме добавления O_APPEND
	}
	free(redirect->redirect_file);
}