#include "../inc/minishell.h"
// Disable readline's default signal handlers
extern int rl_catch_signals;

void sigint_handler(int sig)
{
	(void)sig;
	write(1, "^C\n", 3);             
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
	}
	// Do nothing if prompt is empty
}
void enable_echoctl(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return;
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	setup_signals(void)
{
	rl_catch_signals = 0;

	signal(SIGINT, sigint_handler);
	signal(SIGTERM, SIG_DFL);
	enable_echoctl();
}

// Note: Handle Ctrl+D (EOF) in your main loop: if (!input) { exit/relaunch }eeeee