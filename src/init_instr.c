/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_instr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/20 20:06:44 by scesar			#+#	#+#			 */
/*   Updated: 2025/06/25 12:13:34 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

# include "../inc/minishell.h"

void free_instr (t_instructions *instru)
{

}

// void set_redir(t_instructions *instr, t_commands *cmd)
// {
// 	size_t index;

// 	index = 0;
// 	// instr->redir = malloc(sizeof(t_redir));
// 	while(cmd->args[index])
// 	{
// 		if(cmd->args[index]->type == REDIR_IN || cmd->args[index]->type == HEREDOC)
// 		{
// 			if (cmd->args[index + 1] && cmd->args[index + 1]->type == FILENAME)
// 				add_redir(&instr->in_redir, cmd->args[index]->type, cmd->args[index + 1]->content);
// 			index++;
// 		}
// 		else if(cmd->args[index]->type == REDIR_OUT || cmd->args[index]->type == APPEND)
// 		{
// 			if (cmd->args[index + 1] && cmd->args[index + 1]->type == FILENAME)
// 				add_redir(&instr->out_redir, cmd->args[index]->type, cmd->args[index + 1]->content);
// 			index++;
// 		}
// 		index ++;
// 	}
// }

size_t	tok_to_keep_tab_len(t_token **tokens)
{
	size_t index;
	size_t to_keep;

	index = 0;
	to_keep = 0;
	while (tokens[index])
	{
		if(is_executable_token(tokens[index]->type))
			to_keep++;
		index ++;
	}
	return(to_keep);
}

char **tok_into_tab(t_token **tokens)
{
	size_t i;
	size_t index;
	size_t to_keep;
	char **tab;

	i = 0;
	index = 0;
	to_keep = tok_to_keep_tab_len(tokens);
	tab = malloc(sizeof(char *) * (to_keep + 1));
	if (!tab)
		return (NULL);
	while(tokens[i])
	{
		if(is_executable_token(tokens[i]->type))
		{
			if (tokens[i]->content && tokens[i]->content[0] != '\0') // Check if content is not empty
			{
				tab[index] = ft_strdup(tokens[i]->content);
				if (!tab[index])
				{
					free_tab(tab); // Free previously allocated memory in case of error
					return (NULL); // malloc error
				}
				index++;
			}
		}
		i++;
	}
	tab[index] = NULL;
	return (tab);
}

int init_redir(t_instructions *instr, t_commands *cmd, size_t *index, size_t *in_index, size_t *out_index)
{
	int in_count;
	int out_count;

	in_count = count_redir(&cmd, REDIR_IN);
	out_count = count_redir(&cmd, REDIR_OUT);
	(*index) = 0;
	(*in_index) = 0;
	(*out_index) = 0;
	instr->in_redir = malloc(sizeof(t_redir) * (in_count + 1));
	if(!instr->in_redir)
		return(0);		//malloc error
	instr->out_redir = malloc(sizeof(t_redir) * (out_count + 1));
	if(!instr->out_redir)
		return(0);		//malloc error
	instr->nb_files_in = in_count;
	instr->nb_files_out = out_count;
	instr->in_redir[in_count].file_name = NULL;
	instr->out_redir[out_count].file_name = NULL;
	return(1);
}

t_redir  *add_redir(t_redir *redir_list, t_token_type type, char *file, size_t *io_index)
{
	t_redir *added;

	redir_list[*io_index].file_name = ft_strdup(file);
	if(!redir_list[*io_index].file_name)
		return(NULL);		//malloc error
	redir_list[*io_index].type = type;
	added = &redir_list[*io_index];
	(*io_index) ++;
	return(added);
}


//////// in progress
int set_redir(t_instructions *instr, t_commands *cmd)
{
	size_t index;
	size_t in_index;
	size_t out_index;

	if(!init_redir(instr, cmd, &index, &in_index, &out_index))
		return(0);
	while(cmd->args[index])
	{
		if(cmd->args[index]->type == REDIR_IN || cmd->args[index]->type == HEREDOC)
		{
			if(!add_redir(instr->in_redir, cmd->args[index]->type, cmd->args[index + 1]->content, &in_index))
				return(0);
			index += 2;
		}
		else if(cmd->args[index]->type == REDIR_OUT || cmd->args[index]->type == APPEND)
		{
			if(!add_redir(instr->out_redir, cmd->args[index]->type, cmd->args[index + 1]->content, &out_index))
				return(0);
			index += 2;
		}
		else
			index ++;
	}
	return(1);
}

t_instructions	*init_insrtu(t_minishell *minish, t_commands	*cmd_as_tokens)
{
	size_t	index;
	t_instructions *instru;
	int 		count;

	count = 0;
	index = 0;
	instru = malloc((minish->number_of_commands + 1) * sizeof(t_instructions));
	if(!instru)
		return(NULL);		//malloc error;
	while(cmd_as_tokens)
	{
		ft_bzero(&instru[index], sizeof(t_instructions));
		instru[index].command = ft_strdup(cmd_as_tokens->as_str);
		instru[index].executable = cmd_as_tokens->args;
		count = 0;
		while (instru[index].executable[count] != NULL)
		{
			if(is_executable_token(instru[index].executable[count]->type))
			{
				if(!instru[index].executable[count]->content)
					instru[index].executable[count]->content = ft_strdup("");
				else
					instru[index].executable[count]->content = get_new_string(*minish, instru[index].executable[count]->content);
			}
			printf("content : %s\n", instru[index].executable[count]->content);
			printf("type : %d\n", instru[index].executable[count]->type);
			count++;
		}
		instru[index].path_command = NULL;
		instru[index].in_redir = NULL;
		instru[index].out_redir = NULL;
		if(!set_redir(&instru[index], cmd_as_tokens))
			return(NULL);			//malloc error
		write(2, "passed set redir \n", 19);
		instru[index].exec = tok_into_tab(cmd_as_tokens->args);
		if(!instru[index].exec)
			return(NULL);			//malloc error
		cmd_as_tokens = cmd_as_tokens->next_command;
		write(2, "passed tok into tabs \n", 23);
		index ++;
	}
	ft_bzero(&instru[index], sizeof(t_instructions));				//see if necessary and usable
	return(instru);
}
