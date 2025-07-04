/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free_all.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/20 12:16:28 by scesar			#+#	#+#			 */
/*   Updated: 2025/06/24 16:21:26 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

# include "../inc/minishell.h"

void	exit_shell(char *error_message, t_minishell *minish)
{
	printf("%s", error_message);
	exit(1);
}

void	free_commands(t_commands *cmd)
{
	t_commands *current;
	t_commands *next;
	size_t		index;

	current = cmd;
	next = current->next_command;
	while(current->next_command)
	{
		index = 0;
		while(current->args[index] != NULL)
		{
			free(current->args[index]->content);
			free(current->args[index]);
			index ++;
		}
		free(current->args);
		free(current->as_str);
		current = next;
		next = current->next_command;
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

void free_minish(t_minishell **minish)
{
	if(!minish || !*minish)
		return;
	free_envp((*minish)->envp);
	free(*minish);
	// *minish = NULL; //??
}
