// Jorge Varea Durán

#ifndef GLOBAL_H
#define GLOBAL_H

#include "job_control.h"

typedef struct s_shell
{
	int				exit_status;
	job				*job_l;
}	t_shell;

extern t_shell shell;

#endif
