
#include "../inc/minishell.h"

//will need to free all the as_str !!!
char	*fill_str(t_commands whole_commands, t_commands *current_command, size_t whole_index)
{
	char *res;
	char *temp;

	res = NULL;
	temp = NULL;
	res = ft_strdup(whole_commands.args[whole_index]->content);
	if(!res)
		return(NULL);
	whole_index++;
	while(whole_commands.args[whole_index] && whole_commands.args[whole_index]->type != PIPE)
	{
		temp = ft_strjoin(res, " ");
		free(res);
		if (!temp)
			return (NULL);
		res = ft_strjoin(temp, whole_commands.args[whole_index]->content);
		if(!res)
			return(NULL);
		free(temp);
		whole_index++;
	}
	current_command->as_str = res;
	return(res);
}

size_t count_next_tokens(t_token **whole_commands, size_t index)
{
	size_t tokens;

	tokens = 0;
	while(whole_commands[index] && whole_commands[index]->type != PIPE)
	{
		tokens++;
		index++;
	}
	return(tokens);
}

t_commands *new_command_node()
{
	t_commands *cmd = malloc(sizeof(t_commands));
	if (!cmd)
		return NULL;
	cmd->as_str = NULL;
	cmd->args = NULL;
	cmd->next_command = NULL;
	return (cmd);
}

int tok_type_init(char *content, t_commands *commands, size_t index)
{
	t_token *previous_arg;

	previous_arg = NULL;
	commands->args[index] = malloc(sizeof(t_token));
	if (!commands->args[index])
		return (0); // Handle malloc failure
	commands->args[index]->content = ft_strdup(content);
	if(!commands->args[index]->content)
		return(0);
	if(index > 0)
		previous_arg = commands->args[index - 1];
	if (special_symb_2(content) != NONE )
		commands->args[index]->type = special_symb_2(content);	//see if (char)tab_input[0] prettier
	else if (previous_arg && content[0] == '-' && previous_arg->type == CMD)
		commands->args[index]->type = FLAG;
	else
	{
		if(previous_arg &&
			(previous_arg->type == REDIR_IN || previous_arg->type == REDIR_OUT
			|| previous_arg->type == HEREDOC ||previous_arg->type == APPEND))
			commands->args[index]->type = FILENAME;
		else if (previous_arg && previous_arg->type == CMD)
			commands->args[index]->type = ARG;
		else
			commands->args[index]->type = CMD;
	}
	return(1);
}

void  linker(t_commands whole_commands, t_commands *current_command, size_t *whole_index)
{
	size_t curr_index;
	size_t count;

	curr_index = 0;
	count = count_next_tokens(whole_commands.args, *whole_index);
	current_command->args = malloc(sizeof(t_token *) * (count + 1));
	if(!current_command->args)
		return;  //malloc error
	while(curr_index < count)
	{
		current_command->args[curr_index] = whole_commands.args[*whole_index];
		curr_index++;
		(*whole_index)++;
	}
	current_command->args[curr_index] = NULL;
	if(whole_commands.args[*whole_index] && whole_commands.args[*whole_index]->type == PIPE)
		(*whole_index)++;

}

t_commands  *tokenizer(char *input)
{
	t_commands whole_commands;
	t_commands *first;
	t_commands *current;
	char **tab_input;
	size_t tab_index;
	size_t cmd_index;

	if (!input || *input == '\0')
		return(NULL);
	whole_commands.args = NULL;
	tab_input = ft_split_shell(input);
	if (!tab_input || !tab_input[0])
		return(NULL); // could be empty input or malloc error I think but have to check
	tab_index = 0;
	whole_commands.args = malloc(sizeof(t_token *) * (tab_size(tab_input) + 1));
	if(!whole_commands.args)
	{
		free_tab(tab_input);
		exit(1);		//malloc error
	}
	while(tab_input[tab_index])
	{
		if(!tok_type_init(tab_input[tab_index], &whole_commands, tab_index))
		{
			free_tab(tab_input);
			exit(1);
		}
		tab_index++;
	}
	whole_commands.args[tab_index] = NULL;
	if(!second_check(whole_commands)) //second chek at whole_command, so we still have pipes
	{
		free(whole_commands.args);
		return(NULL);
	}
	cmd_index = 0;
	tab_index = 0;
	first = new_command_node();
	if(!first)
		return (NULL);
	if (!fill_str(whole_commands, first, cmd_index))
		return(NULL);		 //handle errors
	linker(whole_commands, first, &cmd_index);
	current = first;
	while(whole_commands.args[cmd_index])
	{
		current->next_command = new_command_node();
		current = current->next_command;
		if (!fill_str(whole_commands, current, cmd_index))
			return(NULL);		 //handle errors
		linker(whole_commands, current, &cmd_index);
		tab_index++;
	}
	current->next_command = NULL;	  //need this right ?
	free(tab_input);
	free(whole_commands.args);
	return(first);
}
