#include "../inc/minishell.h"

int	run(t_minishell *minish)
{
	int i;

	i = 0;
	if (built_in_parent(minish->instru[0].executable[0]->content) && minish->number_of_commands == 1)
		minish->last_exit_status = exec_builtin(minish->instru[0].executable, minish);
	else
	{
		// print_minishell(minish);
		while (i < minish->number_of_commands)
		{
			if (pipe(minish->fd_pipes[i]) == -1 )
				perror("bablda");				//put an actual message here
			i++;
		}
		process(minish);
	}
	if (ft_strcmp(minish->instru[0].executable[0]->content, "exit") == 0 ) // if the user typed exit
	{
		free_minish(&minish);
		exit(0);
	}
	return (0);
}
void	wait_exit(t_minishell *minish, pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				minish->last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				minish->last_exit_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
}
void	process(t_minishell *minish)
{
	pid_t	forked;
	int		parser;
	pid_t	last_pid;

	last_pid = -1;
	parser = 0;
	while (parser < minish->number_of_commands)
	{
		forked = fork();
		if (forked == -1)
			perror("couldn't fork");
		else if (forked == 0)
		{
			signal(SIGINT, sigint_handler);
    		signal(SIGQUIT, sigquit_handler);
			child_process(minish, &minish->instru[parser], parser);
		}
		else if (parser == minish->number_of_commands - 1)
			last_pid = forked; 
		parser++;
	}
	close_parent(minish);
	wait_exit(minish, last_pid);
}
void	Path_not_found(char *pcommand, t_minishell *minish)
{

	write(2, "bash: ", 6);
	write(2, pcommand, ft_strlen(pcommand));
	write(2, ": No such file or directory\n", 28); // this is the error message for a command not found
	free_minish(&minish);
	close_parent(minish);
	exit(127);
}
void	child_process(t_minishell *minish, t_instructions *instr, int parser)
{
	if (is_builtin(instr->executable[0]->content))
		instr->path_command = instr->executable[0]->content;
	else if (access(instr->executable[0]->content, F_OK) == 0)		//should be X_OK no ? what if PATH is unset ?
		instr->path_command = instr->executable[0]->content;
	else
		instr->path_command = path_finding(instr->executable[0]->content, &minish->envp);
	if (instr->path_command == NULL)
		Path_not_found(instr->executable[0]->content, minish);
	access_test(minish, instr, parser);
	no_redirection_proc(minish, instr, parser);
	if (is_builtin(instr->path_command))
		exec_builtin(instr->executable, minish); 
	else
		execute(minish, instr, parser);
	close_stuff(minish, parser);
	free_minish(&minish);
	exit(0);
}

void	execute(t_minishell *minish, t_instructions *instr, int parser)
{
	int execror;
	char **valid_envp; // this is required to pass the environment variables to the child process
	int len;

	len = env_list_length(minish->envp);
	valid_envp = env_list_to_array(minish->envp, len);
	if (valid_envp == NULL)
		error(minish, "Failed to convert environment variables to array", NULL, 255);
	write(2, "reached execution\n", 19); //see if still necessary
	execror = execve(instr->path_command, instr->exec, valid_envp);
	if (execror == -1)
		error(minish, "execution failed", NULL, 1);
}

void close_parent(t_minishell *minish)
{
	int i;

	i = 0;
	while (i < minish->number_of_commands)
	{
		close(minish->fd_pipes[i][0]);
		close(minish->fd_pipes[i][1]);
        i++;
	}
}

void close_stuff(t_minishell *minish, int parser)
{
	int i;

	i = 0;
	while (i < minish->number_of_commands)
	{
		if (i != parser - 1)
			close(minish->fd_pipes[i][0]); // not reading from this
		if (i != parser)
			close(minish->fd_pipes[i][1]); // not writing to this
        i++;
	}
}

void	error(t_minishell *minish, char *reason, char *specific, int exit_status)
{
	int	index;

	index = 0;
	ft_putstr_fd(specific, 2);
	ft_putstr_fd(reason, 2);
	free_minish(&minish);
	exit(exit_status);
}

