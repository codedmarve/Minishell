
#include "../../includes/minishell.h"

/// @brief closes fd's for input and output redirection.
/// takes two pointers to integers, infile and outfile.
///
/// The function checks:
/// if the fd for infile is not 0, 
/// which represents the standard input, 
/// and if the fd for outfile is not 1, 
/// which represents the standard output. 
/// @param infile 
/// @param outfile 
void	close_files_if_open(int *fd_infile, int *fd_outfile)
{
	if (*fd_infile != 0)
		close(*fd_infile);
	if (*fd_outfile != 1)
		close(*fd_outfile);
}

/// @brief  initializes an input file descriptor 
/// and opens a file for input redirection
///
/// takes a pointer to an integer fd_infile 
/// and a pointer to a character array filename as its args.
///
/// closes the fd if it is already open,
/// opens the file with the given filename in read-only mode, 
/// and assigns the fd to fd_infile. 
/// @param fd_infile 
/// @param filename 
/// @return 
int	init_in_red(int *fd_infile, char *filename)
{
	if (*fd_infile != 0)
		close(*fd_infile);
	*fd_infile = open(filename, O_RDONLY);
	if (*fd_infile == -1)
	{
		printf("in_red error\n");
		return (-1); // errno perror
	}
	return (0);
}

int	init_out_red(int *fd_outfile, char *filename)
{
	if (*fd_outfile != 1)
		close(*fd_outfile);
	*fd_outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*fd_outfile == -1)
	{
		printf("out_red error\n");
		return (-1); // errno perror
	}
	return (0);
}

int	init_app_red(int *fd_outfile, char *filename)
{
	if (*fd_outfile != 1)
		close(*fd_outfile);
	*fd_outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (*fd_outfile == -1)
	{
		printf("app_red error\n");
		return (-1); // errno perror
	}
	return (0);
}



/// @brief handles input and output redirections 
/// in a command line interpreter. 
///
/// initializes two fds for input and output redirect,
/// iterates over the token_lst to check for 
/// input and output redirections.
/// 
/// If an input or output redirection is found, 
/// the corresponding fd is updated using:
/// init_in_red, init_out_red, init_app_red, init_here_doc. 
///
/// Closes any open fds.
/// @param token_lst 
/// @return 
int	redirect_handler(t_token **token_lst)
{
	t_token	*tmp;
	int		fd_infile;
	int		fd_outfile;
	int		value;

	tmp = *token_lst;
	fd_infile = 0;
	fd_outfile = 1;
	while (tmp != NULL)
	{
		if (tmp->type == IN_RED)
			value = init_in_red(&fd_infile, tmp->string);
		else if (tmp->type == OUT_RED)
			value = init_out_red(&fd_outfile, tmp->string);
		else if (tmp->type == APP_RED)
			value = init_app_red(&fd_outfile, tmp->string);
		// else if (tmp->type == HERE_DOC)
		// 	value = init_here_doc(tmp->string);
		if (value == -1)
			break ;
		tmp = tmp->next;
	}
	close_files_if_open(&fd_infile, &fd_outfile);
	return (0);
}
