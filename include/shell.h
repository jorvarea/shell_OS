#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <sys/errno.h>

#include "job_control.h"

# define MAX_ENV_SIZE 4096
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"

typedef struct s_shell
{
	int				exit_status;
	job				*job_l;
}	t_shell;

#endif
