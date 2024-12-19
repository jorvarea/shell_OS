#include "shell.h"

#define MAX_LINE 256

job job_l = {
	.command = "Lista de trabajos",
	.pgid = 0,
	.state = FOREGROUND,
	.next = NULL
};

t_shell shell = {
	.exit_status = 0,
	.job_l = &job_l
};

void child_handler(int signal_id)
{
	job *job;
	int status;
	enum status status_res;
	int info;
    int pid_wait;

	block_SIGCHLD();
	while ((pid_wait = waitpid(-1, &status, WNOHANG)) > 0)
	{
		job = get_item_bypid(shell.job_l, pid_wait);
		if (job != NULL)
		{
			status_res = analyze_status(status, &info);
			if (status_res == EXITED)
			{
				fprintf(stderr, "Background pid: %d, command: %s, %s, info: %d\n", pid_wait, job->command, status_strings[status_res], info);
				delete_job(shell.job_l, job);
			}
			else if (status_res == SUSPENDED)
				job->state = STOPPED;
		}
	}
	unblock_SIGCHLD();
}

int main(void)
{
	char inputBuffer[MAX_LINE];
	char *args[MAX_LINE/2];
	int background;
	char *file_in;
	char *file_out;

	ignore_terminal_signals();
	signal(SIGCHLD, child_handler);

	while (1)
	{   		
		printf(GREEN "shell ➜ " RESET);
		fflush(stdout);
		get_command(inputBuffer, MAX_LINE, args, &background);
		parse_redirections(args, &file_in, &file_out);

		if (args[0] == NULL)
			continue;
		else
			exec_redir_cmd(args, background, file_in, file_out);
	}
	return (0);
}
