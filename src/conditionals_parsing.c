#include "../inc/minishell.h"


bool is_expandable_dollar(const char *string, int str_ind, bool in_double)
{
    if (string[str_ind] != '$')
        return false;
    // Check next character exists
    if (string[str_ind + 1] == '\0')
        return false;
    // Check if next char is '$', '"', or '\''
    if (string[str_ind + 1] == '$')
        return false;
    if (string[str_ind + 1] == ' ')
        return false;
    if (string[str_ind + 1] == '\"' && in_double)
        return false;
    if (string[str_ind + 1] == '\'')
        return false;
    return true;
}