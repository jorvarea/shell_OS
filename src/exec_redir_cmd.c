#include <fcntl.h>

#include "shell.h"
#include "utils.h"

enum file_type { INFILE, OUTFILE };

int open_file(t_shell *shell, char *filename, enum file_type type)
{
	int fd = -1;

	if (type == INFILE)
		fd = open(filename, O_RDONLY);
	else if (type == OUTFILE)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_perror(shell, "open", filename);
	return (fd);
}

void	close_files(int *fd_in, int *fd_out, int n_files_in, int n_files_out)
{
    for (int i = 0; i < n_files_in; i++)
        close(fd_in[i]);
    for (int i = 0; i < n_files_out; i++)
        close(fd_out[i]);
}

void	change_stdio(enum file_type type, int fd)
{
	if (type == INFILE)
		dup2(fd, STDIN_FILENO);
	else if (type == OUTFILE)
		dup2(fd, STDOUT_FILENO);
}

void	execute_redir_cmd(t_shell *shell, char **args, int background, char **file_in, char **file_out)
{
	bool	error;
    int     fd_in[MAX_FDS];
    int     fd_out[MAX_FDS];
    int     n_files_in;
    int     n_files_out;
    int     i = 0;

	error = false;
	while (file_in[i] && !error)
	{
        fd_in[i] = open_file(shell, file_in[i], INFILE);
		if (fd_in[i] != -1)
			change_stdio(INFILE, fd_in[i]);
		else
			error = true;
		i++;
	}
    n_files_in = i;
    i = 0;
    while (file_out[i] && !error)
	{
        fd_out[i] = open_file(shell, file_out[i], OUTFILE);
		if (fd_out[i] != -1)
			change_stdio(OUTFILE, fd_out[i]);
		else
			error = true;
		i++;
	}
    n_files_out = i;
	if (!error)
		exec_cmd(shell, args, background);
	close_files(fd_in, fd_out, n_files_in, n_files_out);
}
