// Jorge Varea Durán

#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <sys/errno.h>

#include "job_control.h"
#include "utils.h"
#include "global.h"

#define MAX_ENV_SIZE 4096

#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"

void	parse_redirections(char **args,  char **file_in, char **file_out);
void	exec_cmd(char **args, int background);
void	exec_redir_cmd(char **args, int background, char *file_in, char *file_out);

#endif
