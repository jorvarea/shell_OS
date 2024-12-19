#include "shell.h"
#include "built_ins.h"
#include "job_control.h"
#include "utils.h"

static void exec_bin(char **args, int background)
{
	pid_t pid_fork;
	int status;
	enum status status_res;
	int info;

	pid_fork = safe_fork();
	if (pid_fork == 0)
	{
		restore_terminal_signals();
		new_process_group(getpid());
        if (background != 1)
        {
            if (set_terminal(getpid()) == -1)
                ft_perror("tcsetpgrp", "");
        }
		if (execvp(args[0], args) == -1)
		{
			if (errno == ENOENT)
			{
				fprintf(stderr, "Error, command not found: %s\n", args[0]);
				exit(127);
			}
			else
			{
				ft_perror("execvp", "");
				exit(1);
			}
		}
	}
    else if (background != 1)
    {
        block_SIGCHLD();
        new_process_group(pid_fork);
        if (set_terminal(pid_fork) == -1)
            ft_perror("tcsetpgrp", "");
        if (waitpid(pid_fork, &status, WUNTRACED) == -1)
            ft_perror("waitpid", "");
        set_terminal(getpid());
        status_res = analyze_status(status, &info);
        if (status_res == SUSPENDED)
            add_job(shell.job_l, new_job(pid_fork, args[0], STOPPED));
        if (info != 127)
            fprintf(stderr, "Foreground pid: %d, command: %s, %s, info: %d\n", pid_fork, args[0], status_strings[status_res], info);
        unblock_SIGCHLD();
    }
    else
    {
        block_SIGCHLD();
        add_job(shell.job_l, new_job(pid_fork, args[0], BACKGROUND));
        fprintf(stderr, "Background job running... pid: %d, command: %s\n", pid_fork, args[0]);
        unblock_SIGCHLD();
    }
}

void exec_cmd(char **args, int background)
{
    if (strcmp(args[0], "cd") == 0)
        cd(args);
    else if (strcmp(args[0], "jobs") == 0)
    {
        block_SIGCHLD();
        print_job_list(shell.job_l);
        unblock_SIGCHLD();
    }
    else if (strcmp(args[0], "fg") == 0)
    {
        block_SIGCHLD();
        fg(args);
        unblock_SIGCHLD();
    }
    else if (strcmp(args[0], "bg") == 0)
    {
        block_SIGCHLD();
        bg(args);
        unblock_SIGCHLD();
    }
    else
        exec_bin(args, background);
}
