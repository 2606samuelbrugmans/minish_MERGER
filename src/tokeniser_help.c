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
	if (!linker(whole, first, &cmd_index))
		return (free_commands(first), NULL);
	printf("After linker\n");
	current = first;
	while (whole.args[cmd_index])
	{
		temp = new_command_node();
		if (!temp)
			return (free_commands(first), NULL);
		write(2, "about to fill", 14);
		if (!fill_str(whole, temp, cmd_index))
			return (free_commands(temp), free_commands(first), NULL);
		write(2, "filled", 7);

		if (!linker(whole, temp, &cmd_index))
			return (free_commands(temp), free_commands(first), NULL);
		write(2, "linked second", 14);
		current->next_command = temp;
		current = current->next_command;
	}
	write(2, "new command\n", 13);
	return (current->next_command = NULL, first);
}

