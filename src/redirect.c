#include "minishell.h"

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