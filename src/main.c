#include "shell.h"

#define MAX_LINE 256

static void	restore_io(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

int main(void)
{
	char inputBuffer[MAX_LINE];
	char *args[MAX_LINE/2];
	int background;             /* equals 1 if a command is followed by '&' */
	char **file_in;
	char **file_out;
	int original_stdin;
	int original_stdout; 
	
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

		original_stdin = dup(STDIN_FILENO);
		original_stdout = dup(STDOUT_FILENO);

		if (args[0] == NULL)
			continue;
		else
			execute_redir_cmd(&shell, args, background, file_in, file_out);

		restore_io(original_stdin, original_stdout);
	}
	// liberar memoria: jobs
	return (0);
}
