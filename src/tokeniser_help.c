#include "../inc/minishell.h"

t_commands	*create_command_list(t_commands whole)
{
	t_commands	*first;
	t_commands	*current;
	t_commands	*temp;
	size_t		cmd_index;

	cmd_index = 0;
	first = new_command_node();
	if (!first)
		return (NULL);
	if (!fill_str(whole, first, cmd_index))
		return (free_commands(first), NULL);
	linker(whole, first, &cmd_index);
	current = first;
	while (whole.args[cmd_index])
	{
		temp = new_command_node();
		if (!temp)
			return (free_commands(first), NULL);
		if (!fill_str(whole, temp, cmd_index))
			return (free(temp), free_commands(first), NULL);
		linker(whole, temp, &cmd_index);
		current->next_command = temp;
		current = temp;
	}
	return (current->next_command = NULL, first);
}

