#include "../inc/minishell.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->content);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
void	free_redirs(t_redir *redir, int count)
{
	int	i;

	i = 0;
	if (!redir)
		return;
	while (i < count)
	{
		free(redir[i].file_name);
		i++;
	}
	free(redir);
}
void	free_commands(t_commands *cmd)
{
	t_commands	*current;
	t_commands	*next;

	current = cmd;
	while (current)
	{
		next = current->next_command;
		free(current->as_str);
		free_tokens(current->args);
		free(current);
		current = next;
	}
}
void free_envp(t_env *env)
{
	t_env *next;

	while(env)
	{
		next = env->next;
		free(env->VAR);
		free(env->value);
		free(env);
		env = next;
	}
}
