
#include "../inc/minishell.h"


bool	is_env_char_end(char c)
{
	return (
		c == ' '  ||
		c == '\"' ||
		c == '$'  ||
		c == '>'  ||
		c == '<'  ||
		c == '\'' ||
		c == '|'  ||
		c == '\0'
	);
}
bool is_executable_token(t_token_type type)
{
	return (
		type == CMD ||
		type == ARG ||
		type == FLAG
	);
}