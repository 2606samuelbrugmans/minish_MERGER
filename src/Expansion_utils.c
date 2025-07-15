#include "../inc/minishell.h"


void append_char(char **dest, char c)
{
	char *temp;
	temp = *dest;
	*dest = ft_strjoinchar(temp, c);
	free(temp);
}

void handle_single_quote(char **dest, const char *str, size_t *i)
{
	char *temp;
	(*i)++;  // skip opening quote
	while (str[*i] && str[*i] != '\'')
	{
		temp = *dest;
		*dest = ft_strjoinchar(temp, str[(*i)++]);
		free(temp);
	}
	if (str[*i] == '\'')
		(*i)++;  // skip closing quote
}

void handle_expand(char **dest, t_minishell ms, const char *str, size_t *i)
{
	char *temp;
	temp = *dest;
	*dest = replace_var(ms, str, i, temp);
}