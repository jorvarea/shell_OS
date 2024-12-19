#include "utils.h"
#include "job_control.h"
#include "shell.h"

void bring_job_foreground(job *background_job)
{
    int status;

    if (set_terminal(background_job->pgid) == -1)
        ft_perror("tcsetpgrp", "");
    background_job->state = FOREGROUND;
    if (killpg(background_job->pgid, SIGCONT) == -1)
        ft_perror("killpg", "SIGCONT");
    if (waitpid(background_job->pgid, &status, WUNTRACED) == -1)
        ft_perror("waitpid", "");
    if (set_terminal(getpid()) == -1)
        ft_perror("tcsetpgrp", "");
    delete_job(shell.job_l, background_job);
}

void fg(char **args)
{
    shell.exit_status = 0;
	if (count_words(args) == 1)
    {
        if (shell.job_l->next)
            bring_job_foreground(shell.job_l->next);
        else
            shell_error("Job not found", 1);
    }
    else if (count_words(args) == 2)
    {
        job *background_job = get_item_bypos(shell.job_l, atoi(args[1]));
        if (background_job == NULL)
            shell_error("Job not found", 1);
        else
            bring_job_foreground(background_job);
    }
    else
		shell_error("fg: too many arguments", 1);
}
