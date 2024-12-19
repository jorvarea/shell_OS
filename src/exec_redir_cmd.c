#include <fcntl.h>

#include "shell.h"
#include "utils.h"

enum file_type { INFILE, OUTFILE };

static int open_file(t_shell *shell, char *filename, enum file_type type)
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

static void	close_files(int fd_in, int fd_out)
{
    if (fd_in != -1)
        close(fd_in);
    if (fd_out != -1)
        close(fd_out);
}

static void	change_stdio(enum file_type type, int fd)
{
	if (type == INFILE)
		dup2(fd, STDIN_FILENO);
	else if (type == OUTFILE)
		dup2(fd, STDOUT_FILENO);
}

static void	restore_io(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

void	exec_redir_cmd(t_shell *shell, char **args, int background, char *file_in, char *file_out)
{
	bool	error;
    int     fd_in;
    int     fd_out;
    int original_stdin = dup(STDIN_FILENO);
	int original_stdout = dup(STDOUT_FILENO);

	error = false;
	if (file_in)
	{
        fd_in = open_file(shell, file_in, INFILE);
		if (fd_in != -1)
			change_stdio(INFILE, fd_in);
		else
			error = true;
	}
    if (file_out)
	{
        fd_out = open_file(shell, file_out, OUTFILE);
		if (fd_out != -1)
			change_stdio(OUTFILE, fd_out);
		else
			error = true;
	}
	if (!error)
		exec_cmd(shell, args, background);
	close_files(fd_in, fd_out);
    restore_io(original_stdin, original_stdout);
}
