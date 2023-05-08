
#include "../../includes/minishell.h"

// Ctrl+C: Sends the SIGINT (Interrupt) signal to the foreground process group.
// Used to stop the currently running command or process.

// Interactive shell: Terminates the running command or process.

// Non-interactive shell: Typically has no effect as there is no keyboard input.

// Heredoc: Cancels the heredoc input, returns to the command prompt.


// Ctrl+D: Sends an End-Of-File (EOF) character, 
// which indicates that no more data will be sent.

// Interactive shell: If there is no text on the current line,
// it will exit the shell. If there is text,
// it will attempt to execute that text as a command.

// Non-interactive shell: Typically has no effect as there is no keyboard input.

// Heredoc: Ends the heredoc input and continues processing the script.


// Ctrl+Backslash: Sends the SIGQUIT (Quit) signal to the foreground 
// process group.
// This causes the process to terminate and dump core
// (if core dumping is enabled).

// Interactive shell: Terminates the running command or process 
// and generates a core dump if enabled.

// Non-interactive shell: Typically has no effect as there is no keyboard input.

// Heredoc: Usually has no effect, as Ctrl+Backslash is 
// not used in heredoc contexts.

/// @brief helper function for sig_interactive
void	ignore_ctrl_bslash(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/// @brief helper function for sig_interactive
/// @param sig 
void	ctrl_c_interactive(int sig)
{
	// (void)sig;

	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// /// @brief default signal flow
// /// ctrl-backslash is ignored
// /// ctrl-C displays new prompt
// /// @param  
void	sig_interactive(void) // DEFAULT STATE
{
	struct sigaction	sa;

	ignore_ctrl_bslash();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ctrl_c_interactive;
	sigaction(SIGINT, &sa, NULL);
}

/////////////////////////////////////////////

/// @brief helper function for sig_noninteractive
/// @param sig 
void	ctrl_c_ctrl_bslash_noninteractive(int sig)
{
	// (void)sig;

	// if (sig == SIGQUIT)
	// 	write(1, "quit", 4);
	write(1, "\n", 1);
	rl_on_new_line();
}

/// @brief for child processes usage
/// @param  
void	sig_noninteractive(void) // CHILD PROCESS
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ctrl_c_ctrl_bslash_noninteractive;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/////////////////////////////////////////////
void ctrl_c_heredoc(int sig)
{
	//(void)sig;

	if (sig == SIGINT)
		// return ;
		exit(1);
}


void	sig_heredoc(void)
{
	struct sigaction	sa;

	ignore_ctrl_bslash();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &ctrl_c_heredoc;
	sigaction(SIGINT, &sa, NULL);
}


void	sig_parent_heredoc(void)
{
	struct sigaction	sa;

	ignore_ctrl_bslash();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}


// void signal_child_active(void) {
//     struct sigaction sa;

//     memset(&sa, 0, sizeof(sa));
//     sa.sa_handler = SIG_DFL;

//     sigaction(SIGINT, &sa, NULL);
//     sigaction(SIGQUIT, &sa, NULL);
// }
