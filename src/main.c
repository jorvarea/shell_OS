#include "shell.h"

#define MAX_LINE 256

int main(void)
{
	char inputBuffer[MAX_LINE];
	char *args[MAX_LINE/2];
	int background;
	char *file_in;
	char *file_out;
	
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
		parse_redirections(args, &file_in, &file_out);

		if (args[0] == NULL)
			continue;
		else
			exec_redir_cmd(&shell, args, background, file_in, file_out);
	}
	// liberar memoria: jobs
	return (0);
}
