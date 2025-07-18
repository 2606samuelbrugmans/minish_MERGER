#include "../inc/minishell.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		printf("free tok %p  content %p\n",
       (void*)tokens[i],
       (void*)tokens[i]->content);
		free(tokens[i]->content);
		free(tokens[i]);
		i++;
	}
	printf("free_tokens: freeing tokens array at %p\n", (void*)tokens);
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
void free_commands(t_commands *cmd)
{
	t_commands *current;
	t_commands *next;

	current = cmd;
	while (current)
	{
		next = current->next_command;
		printf("free_commands: freeing as_str at %p\n", (void*)current->as_str);
		free(current->as_str);
		free_tokens(current->args);
		printf("free_commands: freeing command node at %p\n", (void*)current);
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
void free_array(char ***array)
{
	int i;

	if (!array || !*array)
		return;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}
void	free_tokens_partial(t_token **tokens)
{
	if (!tokens)
		return;
	free(tokens);  // only the array, not what it points to
}