
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