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
	int status;
    int pid_wait;

	block_SIGCHLD();
    pid_wait = waitpid(-1, &status, WNOHANG | WCONTINUED | WUNTRACED);
    
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

	while (1)
	{   		
		printf(GREEN "COMMAND->" RESET);
		fflush(stdout);
		get_command(inputBuffer, MAX_LINE, args, &background);
		parse_redirections(args, &file_in, &file_out);

		if (args[0] == NULL)
			continue;
		else
			exec_redir_cmd(args, background, file_in, file_out);
	}
	// liberar memoria: jobs
	return (0);
}
