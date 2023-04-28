
#include "../../includes/minishell.h"

/// @brief helper function for sig_interactive
void	ignore_ctrl_backslash(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/// @brief helper function for sig_interactive
/// @param sig 
void	ctrl_c(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/// @brief default signal flow
/// ctrl-backslash is ignored
/// ctrl-D exits the shell
/// ctrl-C displays new prompt
/// @param  
void	sig_interactive(void)
{
	struct sigaction	sa;

	ignore_ctrl_backslash();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ctrl_c;
	sigaction(SIGINT, &sa, NULL);
}

/////////////////////////////////////////////

/// @brief helper function for sig_noninteractive
/// @param sig 
void	display_newline(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
		write(1, "quit", 4);
	write(1, "\n", 1);
	rl_on_new_line();
}

/// @brief for child processes usage
/// @param  
void	sig_noninteractive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &display_newline;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/////////////////////////////////////////////
void ctrl_c_heredoc(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		exit(1);
}

void	sig_heredoc(void)
{
	struct sigaction	sa;

	ignore_ctrl_backslash();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ctrl_c_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

