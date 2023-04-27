
#include "../../includes/minishell.h"
// // 12. Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
// // there are signals

// // 13. In interactive mode:
// // ◦ ctrl-C displays a new prompt on a new line. ◦ ctrl-D exits the shell.
// // ◦ ctrl-\ does nothing.

void	sigquit_sig_ign(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	prompt_reset(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_interactive(void)
{
	struct sigaction	sa;

	sigquit_sig_ign(); // CTRL + \ = SIGQUIT
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &prompt_reset;
	sigaction(SIGINT, &sa, NULL);
}

void	newline_reset(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	sig_noninteractive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &newline_reset;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
