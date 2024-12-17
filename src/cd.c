#include "utils.h"

static void	change_directory(t_shell *shell, char *path)
{
	char	pwd[MAX_ENV_SIZE];
	char	oldpwd[MAX_ENV_SIZE];

	if (getcwd(oldpwd, MAX_ENV_SIZE))
	{
		if (chdir(path) == 0)
		{
			if (getcwd(pwd, MAX_ENV_SIZE))
			{
				setenv("OLDPWD", strdup(oldpwd), 1);
				setenv("PWD", strdup(pwd), 1);
			}
			else
				ft_perror(shell, "getcwd", "");
		}
		else
			ft_perror(shell, "chdir", path);
	}
	else
		ft_perror(shell, "getcwd", "");
}

static void	take_me_home(t_shell *shell)
{
	char	*home;

	home = getenv("HOME");
	if (home)
		change_directory(shell, home);
	else
		shell_error(shell, "-shell: cd: HOME not set");
}

static void	take_me_back(t_shell *shell)
{
	char	pwd[MAX_ENV_SIZE];
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (oldpwd)
	{
		change_directory(shell, oldpwd);
		if (getcwd(pwd, MAX_ENV_SIZE))
			printf("%s\n", pwd);
		else
			ft_perror(shell, "getcwd", "");
	}
	else
		shell_error(shell, "-shell: cd: OLDPWD not set");
}

static void	process_cd_args(t_shell *shell, char **args)
{
	if (!args[1])
		take_me_home(shell);
	else if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		take_me_back(shell);
	else
		change_directory(shell, args[1]);
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
