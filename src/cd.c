#include "utils.h"

static void	take_me_back(t_shell *shell)
{
	char	pwd[MAX_ENV_SIZE];
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (oldpwd)
	{
		chdir(oldpwd);
		if (getcwd(pwd, MAX_ENV_SIZE))
			printf("%s\n", pwd);
		else
			ft_perror(shell, "getcwd", "");
		free(oldpwd);
	}
	else
		shell_error(shell, "-shell: cd: OLDPWD not set");
}

static void	process_cd_args(t_shell *shell, char **args)
{
	char	*home;

	if (!args[1])
	{
		home = getenv("HOME");
		chdir(home);
		free(home);
	}
	else if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		take_me_back(shell);
	else
		chdir(args[1]);
}

void	cd(t_shell *shell, char **args)
{
	shell->exit_status = 0;
	if (found_flags(args))
		invalid_flag_error(shell, "cd", args[1][1], "cd [dir]");
	else if (count_words(args) > 2)
		shell_error(shell, "-shell: cd: too many arguments");
	else
		process_cd_args(shell, args);
}
