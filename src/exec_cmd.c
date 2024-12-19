#include "shell.h"
#include "built_ins.h"
#include "job_control.h"
#include "utils.h"

static void exec_bin(t_shell *shell, char **args, int background)
{
	pid_t pid_fork;
	int status;
	enum status status_res;
	int info;

	pid_fork = safe_fork();
	if (pid_fork == 0)
	{
		new_process_group(0);
		restore_terminal_signals();
		if (execvp(args[0], args) == -1)
		{
			if (errno == ENOENT)
			{
				fprintf(stderr, "Error, command not found: %s\n", args[0]);
				exit(127);
			}
			else
			{
				ft_perror(shell, "execvp", "");
				exit(1);
			}
		}
	}
	else if (background != 1)
	{
		set_terminal(pid_fork);
		waitpid(pid_fork, &status, WUNTRACED);
		set_terminal(getpid());
		status_res = analyze_status(status, &info);
		if (info != 127)
			printf("Foreground pid: %d, command: %s, %s, info: %d\n", pid_fork, args[0], status_strings[status_res], info);
	}
	else
	{
		add_job(shell->job_l, new_job(pid_fork, args[0], BACKGROUND));
		printf("Background job running... pid: %d, command: %s\n", pid_fork, args[0]);
	}
}

void exec_cmd(t_shell *shell, char **args, int background)
{
    if (strcmp(args[0], "cd") == 0)
        cd(shell, args);
    else if (strcmp(args[0], "jobs") == 0)
        print_job_list(shell->job_l);
    else if (strcmp(args[0], "fg") == 0)
        fg(shell, args);
    else
        exec_bin(shell, args, background);
}
