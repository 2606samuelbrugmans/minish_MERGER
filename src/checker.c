#include "../inc/minishell.h"

int unclosed_quotes(char *input)
{
	size_t index;

	index = 0;
	while(input[index])
	{
		if(input[index] == '\'' || input[index] == '\"')
		{
			if (end_quotes(input, &index) == 0)
				return(YES);
		}
		else
			index ++;
	}
	return(NOPE);
}

int first_check(char *input)
{
	size_t index;

	index = 0;

	if (unclosed_quotes(input))
	{
		minish->last_exit_status = 2;
		printf("Syntax error: Unclosed quotes.\n");
		return(0);
	}
	while(input[index] == ' ')
		index ++;
	if(input[index] == '|')
	{
		minish->last_exit_status = 2;
		printf("Syntax error near unexpected token `|'\n");
		return(0);
	}
	//not sure about this check
	while(input[index])
	{
		if((unsigned char)input[index] < 32 && input[index] != '\t' && input[index] != '\n')
		{
			minish->last_exit_status = 2;
			printf("Syntax error: Unescaped character: ASCII %d\n", input[index]);
			return(0);
		}
		index ++;
	}
	return(1);
}

int second_check(t_commands whole_commands)
{
	size_t index;
	t_token *next;

	index = 0;
	next = NULL;
	while(whole_commands.args[index])
	{
		next = whole_commands.args[index + 1];
		if (!redir_check(whole_commands.args[index], next))
			return(0);
		if (!pipe_check(whole_commands.args[index], next))
			return(0);
		index ++;
	}
	return(1);
}

int redir_check(t_token *current, t_token *next)
{
	if(current->type == (REDIR_IN) || current->type == (REDIR_OUT)
		|| current->type == (HEREDOC) || current->type == (APPEND))
	{
		if(!next)
		{
			minish->last_exit_status = 2;
			printf("Syntax error near unexpected token `newline'\n");
			return(0);
		}
		if(next->type != FILENAME)
		{
			minish->last_exit_status = 2;
			printf("Syntax error near unexpected token `%s'\n", next->content);
			return(0);
		}
	}
	return(1);
}

int pipe_check(t_token *current, t_token *next)
{
	if(current->type == PIPE)
	{
		if(!next)
		{
			printf("Syntax error near unexpected token `newline'\n");
			minish->last_exit_status = 2;
			return(0);
		}
		if(next->type == PIPE)
		{
			minish->last_exit_status = 2;
			printf("Syntax error near unexpected token `|'\n");
			return(0);
		}
	}
	return(1);
}
