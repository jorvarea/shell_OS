#include "utils.h"
#include "job_control.h"
#include "shell.h"

void bring_job_foreground(t_shell *shell, job *background_job)
{
    int status;

    if (set_terminal(background_job->pgid) == -1)
        ft_perror(shell, "tcsetpgrp", "");
    background_job->state = FOREGROUND;
    if (killpg(background_job->pgid, SIGCONT) == -1)
        ft_perror(shell, "killpg", "SIGCONT");
    if (waitpid(background_job->pgid, &status, WUNTRACED) == -1)
        ft_perror(shell, "waitpid", "");
    if (set_terminal(getpid()) == -1)
        ft_perror(shell, "tcsetpgrp", "");
    delete_job(shell->job_l, background_job);
}

void fg(t_shell *shell, char **args)
{
    shell->exit_status = 0;
	if (found_flags(args))
		invalid_flag_error(shell, "cd", args[1][1], "fg [job_spec]");
	else if (count_words(args) == 1)
    {
        if (shell->job_l->next)
            bring_job_foreground(shell, shell->job_l->next);
        else
            shell_error(shell, "fg: current: no such job", 1);
    }
    else if (count_words(args) == 2)
    {
        job *background_job = get_item_bypos(shell->job_l, atoi(args[1]));
        if (background_job == NULL)
            shell_error(shell, "fg: no such job", 1);
        else
            bring_job_foreground(shell, background_job);        
    }
    else
		shell_error(shell, "fg: too many arguments", 1);
}