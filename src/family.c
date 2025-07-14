#include "../inc/minishell.h"

int	run(t_minishell *minish)
{
	int i;

	i = 0;
	if (built_in_parent(minish->instru[0].executable[0]->content) && minish->number_of_commands == 1)
		minish->last_exit_status = exec_builtin(minish->instru[0].exec, minish);
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

	return (0);
}
void	wait_exit(t_minishell *minish, pid_t	last_pid)
{
	int index;
	pid_t wait_pid;
	int status;

	index = 0;
	while (index < minish->number_of_commands)
	{
		wait_pid = wait(&status);
		if (wait_pid == last_pid)
		{
			if (WIFEXITED(status))
				minish->last_exit_status = WEXITSTATUS(status);  
			else if (WIFSIGNALED(status))
				minish->last_exit_status = 128 + WTERMSIG(status); 
		}
		index++;
	}

}
void	process(t_minishell *minish)
{
	pid_t	forked;
	int		parser;
	pid_t	last_pid;

	last_pid = -1;
	parser = 0;
	signal(SIGINT, SIG_IGN);
	while (parser < minish->number_of_commands)
	{
		forked = fork();
		if (forked == -1)
			perror("couldn't fork");
		else if (forked == 0)
		{
			signal(SIGINT, SIG_DFL);    
			signal(SIGQUIT, SIG_DFL);   
			child_process(minish, &minish->instru[parser], parser);
		}
		else if (parser == minish->number_of_commands - 1)
			last_pid = forked;
		parser++;
	}
	close_parent(minish);
	wait_exit(minish, last_pid);
	signal(SIGINT, sigint_handler);
}
void	Path_not_found(char *pcommand, t_minishell *minish)
{

	write(2, "bash: ", 6);
	write(2, pcommand, ft_strlen(pcommand));
	write(2, ": command not found\n", 21); // this is the error message for a command not found
	close_parent(minish);
	free_minish_total(&minish);
	exit(127);
}
void	child_process(t_minishell *minish, t_instructions *instr, int parser)
{
	if (is_builtin(instr->exec[0]))
		instr->path_command = instr->exec[0];
	else
		instr->path_command = path_finding(instr->exec[0], &minish->envp);
	if (instr->path_command == NULL)
		Path_not_found(instr->exec[0], minish);
	access_test(minish, instr, parser);
	no_redirection_proc(minish, instr, parser);
	if (is_builtin(instr->path_command))
		exec_builtin(instr->exec, minish); 
	else
		execute(minish, instr, parser);
	close_stuff(minish, parser);
	free_minish_total(&minish);
	exit(0);
}
void	print_env_array(char **envp)
{
	int i = 0;
	printf("\n printing the ARRAY:\n");
	while (envp[i])
	{
		printf("  [%d]: %s\n", i, envp[i]);
		i++;
	}
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
	free_minish_total(&minish);
	exit(exit_status);
}

