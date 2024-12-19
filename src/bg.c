#include "shell.h"

void continue_job_background(job *background_job)
{
    background_job->state = BACKGROUND;
    if (killpg(background_job->pgid, SIGCONT) == -1)
        ft_perror("killpg", "SIGCONT");
}

void bg(char **args)
{
    shell.exit_status = 0;
	if (count_words(args) == 1)
    {
        if (shell.job_l->next)
            continue_job_background(shell.job_l->next);
        else
            shell_error("Job not found", 1);
    }
    else if (count_words(args) == 2)
    {
        job *background_job = get_item_bypos(shell.job_l, atoi(args[1]));
        if (background_job == NULL)
            shell_error("Job not found", 1);
        else
            continue_job_background(background_job);
    }
    else
		shell_error("fg: too many arguments", 1);
}