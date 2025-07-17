/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:45:59 by scesar            #+#    #+#             */
/*   Updated: 2025/07/15 15:19:29 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	exit_shell(char *error_message, t_minishell **minish)
{
	free_minish_total(minish);
	write(2, error_message, ft_strlen(error_message));
	exit(-1);
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
 	if((*minish)->parsed_string)
 		free((*minish)->parsed_string);
 	if ((*minish)->fd_pipes)
 		free((*minish)->fd_pipes);
 	if ((*minish)->instru)
 		free_instructions((*minish)->instru, (*minish)->number_of_commands);
	(*minish)->instru = NULL;
	(*minish)->number_of_commands = 0;
	(*minish)->fd_pipes = NULL;
 }

void	free_minish_total(t_minishell **minish)
{
	if (!minish || !*minish)
		return ;
	if ((*minish)->envp)
		free_envp((*minish)->envp);
	if ((*minish)->local_var)
		free_envp((*minish)->local_var);
	if((*minish)->parsed_string)
		free((*minish)->parsed_string);
	if ((*minish)->instru)
		free_instructions((*minish)->instru, (*minish)->number_of_commands);
	if ((*minish)->fd_pipes)
		free((*minish)->fd_pipes);
	free(*minish);
	*minish = NULL;
}
