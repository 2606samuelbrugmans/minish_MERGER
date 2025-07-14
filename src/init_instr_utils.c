# include "../inc/minishell.h"

t_token **init_executable(t_token **cmd_as_tokens, t_instructions *instru, int index, t_minishell *minish)
{
	int count;

	count = 0;
	instru[index].executable = (cmd_as_tokens);
	while (instru[index].executable[count] != NULL)
	{
		if(is_executable_token(instru[index].executable[count]->type))
		{
			if(!instru[index].executable[count]->content)
				instru[index].executable[count]->content = ft_strdup("");
			else
				instru[index].executable[count]->content = get_new_string(*minish, instru[index].executable[count]->content);
		}
		count++;
	}
	return (instru[index].executable);
}
