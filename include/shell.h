#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

# define MAX_ENV_SIZE 4096

typedef struct s_shell
{
	int				exit_status;
}	t_shell;

#endif
