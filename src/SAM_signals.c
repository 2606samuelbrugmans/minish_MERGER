#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

// Disable readline's default signal handlers
rl_catch_signals = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	// just print a newline and reset the prompt
	// this is the behavior for ctrl+C (SIGINT)
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

}

void	sigquit_handler(int sig)
{
	(void)sig;
	// if the line buffer is not empty
	/// print "Quit: 3" and exit with status 131
	// this is the behavior for Ctrl+\ (SIGQUIT)
	if (rl_line_buffer && *rl_line_buffer != '\0')
	{
		write(1, "Quit: 3\n", 8);
		exit(131); 
	}
	// Do nothing if prompt is empty
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTERM, SIG_DFL);
}

// Note: Handle Ctrl+D (EOF) in your main loop: if (!input) { exit/relaunch }