#include "shell.h"
#include "utils.h"

static void	change_directory(char *path)
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
				ft_perror("getcwd", "");
		}
		else
			ft_perror("chdir", path);
	}
	else
		ft_perror("getcwd", "");
}

static void	take_me_home()
{
	char	*home;

	home = getenv("HOME");
	if (home)
		change_directory(home);
	else
		shell_error("-shell: cd: HOME not set", 1);
}

static void	take_me_back()
{
	char	pwd[MAX_ENV_SIZE];
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (oldpwd)
	{
		change_directory(oldpwd);
		if (getcwd(pwd, MAX_ENV_SIZE))
			printf("%s\n", pwd);
		else
			ft_perror("getcwd", "");
	}
	else
		shell_error("-shell: cd: OLDPWD not set", 1);
}

static void	process_cd_args(char **args)
{
	if (!args[1])
		take_me_home();
	else if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		take_me_back();
	else
		change_directory(args[1]);
}

void	cd(char **args)
{
	shell.exit_status = 0;
	if (found_flags(args))
		invalid_flag_error("cd", args[1][1], "cd [dir]");
	else if (count_words(args) > 2)
		shell_error("-shell: cd: too many arguments", 1);
	else
		process_cd_args(args);
}
