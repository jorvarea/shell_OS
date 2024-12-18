#include "job_control.h"
#include "utils.h"
#include "shell.h"
#include "built_ins.h"

#define MAX_LINE 256

void execute_cmd(t_shell *shell, char **args, int background)
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
	else if (background == 0)
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

int main(void)
{
	char inputBuffer[MAX_LINE];
	char *args[MAX_LINE/2];
	int background;             /* equals 1 if a command is followed by '&' */
	
	job job_l = {
		.command = "Lista de trabajos",
		.pgid = 0,
		.state = 0,
		.next = NULL
	};

	t_shell shell = {
		.exit_status = 0,
		.job_l = &job_l
	};

	ignore_terminal_signals();

	while (1)
	{   		
		printf(GREEN "COMMAND->" RESET);
		fflush(stdout);
		get_command(inputBuffer, MAX_LINE, args, &background);
		
		if (args[0] == NULL) 
			continue;
		else if (strcmp(args[0], "cd") == 0)
			cd(&shell, args);
		else if (strcmp(args[0], "jobs") == 0)
			print_job_list(&job_l);
		else if (strcmp(args[0], "fg") == 0)
			fg(&shell, args);
		else
			execute_cmd(&shell, args, background);
	}
	// liberar memoria: jobs
	return (0);
}
