#include "shell.h"

void	invalid_flag_error(t_shell *shell, char *cmd, char invalid_flag, char *usage)
{
	shell->exit_status = 2;
	fprintf(stderr, "-shell: %s: -%c: invalid option\n", cmd, invalid_flag);
	fprintf(stderr, "%s: usage: %s\n", cmd, usage);
}

void	shell_error(t_shell *shell, char *msg)
{
	shell->exit_status = 1;
	fprintf(stderr, "%s\n", msg);
}

void	ft_perror(t_shell *shell, char *function, char *arg)
{
	shell->exit_status = 1;
	printf("-shell: ");
	if (function && function[0] != '\0')
		printf("%s: ", function);
	if (arg && arg[0] != '\0')
		printf("%s: ", arg);
	printf("%s\n", strerror(errno));
}

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

bool	found_flags(char **args)
{
	bool	found;

	found = false;
	if (args[1] && args[1][0] == '-' && args[1][1] && args[1][1] != '-')
		found = true;
	return (found);
}

int	count_words(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
		i++;
	return (i);
}
