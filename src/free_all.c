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

void	free_instructions(t_instructions *instru, int count)
{
	int	i;
	int	j;

	if (!instru)
		return ;
	i = 0;
	while (i < count)
	{
		free_tokens(instru[i].executable);
		free(instru[i].command);
		free_redirs(instru[i].in_redir, instru[i].nb_files_in);
		free_redirs(instru[i].out_redir, instru[i].nb_files_out);
		if (instru[i].exec)
		{
			j = 0;
			while (instru[i].exec[j])
			{
				free(instru[i].exec[j]);
				j++;
			}
			free(instru[i].exec);
		}
		free(instru[i].path_command);
		i++;
	}
	free(instru);
}

void	free_minish_partial(t_minishell **minish)
{
	if (!minish || !*minish)
		return ;
	free((*minish)->parsed_string);
	if ((*minish)->fd_pipes)
		free((*minish)->fd_pipes);
	free_instructions((*minish)->instru, (*minish)->number_of_commands);
}

void	free_minish_total(t_minishell **minish)
{
	if (!minish || !*minish)
		return ;
	free_envp((*minish)->envp);
	free_envp((*minish)->local_var);
	free((*minish)->parsed_string);
	if ((*minish)->fd_pipes)
		free((*minish)->fd_pipes);
	free_instructions((*minish)->instru, (*minish)->number_of_commands);
	free(*minish);
	*minish = NULL;
}