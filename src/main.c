#include "job_control.h"
#include "utils.h"
#include "shell.h"
#include "built_ins.h"

#define MAX_LINE 256

void init_signal_handlers()
{
	signal(SIGINT, SIG_IGN);
}

void restore_signal_handlers()
{
	signal(SIGINT, SIG_DFL);
}

int main(void)
{
	char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
	int background;             /* equals 1 if a command is followed by '&' */
	char *args[MAX_LINE/2];     /* command line (of 256) has max of 128 arguments */

	pid_t pid_fork, pid_wait; /* pid for created and waited process */
	int status;             /* status returned by wait */
	enum status status_res; /* status processed by analyze_status() */
	int info;				/* info processed by analyze_status() */
	t_shell shell;

	shell.exit_status = 0;
	ignore_terminal_signals();

	while (1)   /* Program terminates normally inside get_command() after ^D is typed*/
	{   		
		printf(GREEN "COMMAND->" RESET);
		fflush(stdout);
		get_command(inputBuffer, MAX_LINE, args, &background);
		
		if (args[0] == NULL) 
			continue;
		else if (strcmp(args[0], "cd") == 0)
			cd(&shell, args);
		else
		{
			pid_fork = safe_fork();
			if (pid_fork == 0)
			{
				restore_terminal_signals();
				if (execvp(args[0], args) == -1)
					ft_perror(&shell, "execvp", NULL);
			}
			else
				waitpid(pid_fork, &status, 0);
		}

		/* the steps are:
			 (1) fork a child process using fork()
			 (2) the child process will invoke execvp()
			 (3) if background == 0, the parent will wait, otherwise continue 
			 (4) Shell shows a status message for processed command 
			 (5) loop returns to get_commnad() function
		*/

	}
}
