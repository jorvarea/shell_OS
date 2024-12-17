#ifndef UTILS_H
#define UTILS_H

#include "shell.h"

void	invalid_flag_error(t_shell *shell, char *cmd, char invalid_flag, char *usage);
void	shell_error(t_shell *shell, char *msg);
void	ft_perror(t_shell *shell, char *function, char *arg);
bool	found_flags(char **args);
int     count_words(char **ptr);
pid_t	safe_fork(void);

#endif