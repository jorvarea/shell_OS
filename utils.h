// Jorge Varea Durán

#ifndef UTILS_H
#define UTILS_H

#include "shell.h"

void	invalid_flag_error(char *cmd, char invalid_flag, char *usage);
void	shell_error(char *msg, int exit_status);
void	ft_perror(char *function, char *arg);
bool	found_flags(char **args);
int     count_words(char **ptr);
pid_t	safe_fork(void);

#endif