/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   loc_var.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/24 19:32:43 by scesar			#+#	#+#			 */
/*   Updated: 2025/06/24 19:48:05 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minishell.h"

char *valid_var_add(char *input)	//check if enough protection
{
	size_t i;
	char *equal;

	if(!input || input[0] == '=' || ft_isdigit(input[0]))
		return (NULL);
	equal = ft_strchr(input, '=');
	if(!equal)
		return (NULL);
	i = 0;
	while(input[i] && input[i] != '=')
	{
		if(!ft_isalnum(input[i]))
			return(NULL);
		i++;
	}
	return(equal);
}

int	update_val(t_env **minish_envp, t_env **minish_local_var, t_env *next_var, char *after_equal, char *to_free)
{
	if(to_free)
		free(to_free);
	if(next_var->value)
		free(next_var->value);
	next_var->value = ft_strdup(after_equal);
	if(!next_var->value)
		return(0);
	return(1);
}

int add_loc_var(t_env **minish_envp, t_env **minish_local_var, char *input)
{
	t_env *last_var;
	t_env *next_var;
	char *equal;
	char *pres_var;

	equal = valid_var_add(input);
	if (!equal)
		return(0);
	pres_var = ft_substr(input, 0, equal - input);
	if(!pres_var)
		return(0);
	next_var = get_VAR(minish_envp, minish_local_var, pres_var);
	if(next_var != NULL)
		return(update_val(minish_envp, minish_local_var, next_var, equal + 1, pres_var));						//malloc error
	set_next_var(&next_var, input, equal);
	next_var->next = NULL;
	if(!*minish_local_var)
		*minish_local_var = next_var;
	else
	{
		last_var = *minish_local_var;
		while(last_var->next)
			last_var = last_var->next;
		last_var->next = next_var;
	}
	return(1);
}

// int add_loc_var(t_env **minish_envp, t_env **minish_local_var, char *input)
// {
// 	t_env *last_var;
// 	t_env *next_var;
// 	char *equal;
// 	size_t key_len;

// 	// last_var = NULL;
// 	// next_var = NULL;
// 	equal = valid_var_add(input);
// 	if (!equal)
// 		return(0);
// 	next_var = malloc(sizeof(t_env));
// 	if(!next_var)
// 		return(0);							//malloc error
// 	next_var->VAR = ft_substr(input, 0, equal - input);
// 	next_var->value = ft_strdup(equal + 1);
// 	if(var_already_there(minish_envp, minish_local_var, next_var->VAR))
// 	{
// 		free(get_VAR(minish_envp, minish_local_var, next_var->VAR)->value);
// 		get_VAR(minish_envp, minish_local_var, next_var->VAR)->value = next_var->value;
// 		free((next_var)->VAR);	//should I free it in var_already_there ?
// 		free(next_var);
// 		return(1);
// 	}
// 	next_var->next = NULL;
// 	if(!*minish_local_var)
// 		*minish_local_var = next_var;
// 	else
// 	{
// 		last_var = *minish_local_var;
// 		while(last_var->next)
// 			last_var = last_var->next;
// 		last_var->next = next_var;
// 	}
// 	return(1);
// }

char *dollar_interrogation(t_minishell minishell, char *string, size_t **str_ind, char *temp)
{
	char *exit_status_str;
	char *renew_str;
	
	if (string[**str_ind] != '?')
		return( temp);
	exit_status_str = NULL;
	exit_status_str = ft_itoa(minishell.last_exit_status); // Convert int to string
	if (!exit_status_str)
		return (NULL); // malloc error
	renew_str = ft_strjoin(temp, exit_status_str); // Append to temp$µ
	if (!renew_str)
		return (free(exit_status_str), NULL); // malloc error
	free(exit_status_str);
	(**str_ind)++; // Move index forward
	return (renew_str);
}

char *replace_var(t_minishell minishell, char *string, size_t *str_ind, char *temp)
{
	size_t len_var;
	t_env *actual_var;
	char *pres_var;
	char *renew_str;

	len_var = 0;
	(*str_ind)++;
	if (string[*str_ind] == '?')
		return (dollar_interrogation(minishell, string, &str_ind, temp));
	while(!is_env_char_end(string[*str_ind + len_var]))
		len_var++;
	pres_var = ft_substr(string, *str_ind, len_var);
	if(!pres_var)
		return( NULL);	   //malloc error;
	(*str_ind) += len_var;
	actual_var = get_VAR(&minishell.envp, &minishell.local_var, pres_var);
	if(actual_var)
		renew_str = ft_strjoin(temp, actual_var->value);
	else
		renew_str = ft_strjoin(temp, "");
	return (free(pres_var), renew_str);
}

char *get_new_string(t_minishell minishell, char *string)
{
	char *new_str;
	bool in_double;
	size_t str_ind;

	in_double  = false;
	str_ind = 0;
	new_str = ft_strdup("");
	if (!new_str)
		return NULL;
	while (string[str_ind])
	{
		if (string[str_ind] == '\"')
			in_double = !in_double, str_ind++;
		else if (string[str_ind] == '\'' && !in_double)
			handle_single_quote(&new_str, string, &str_ind);
		else if (is_expandable_dollar(string, str_ind, in_double))
			handle_expand(&new_str, minishell, string, &str_ind);
		else
			append_char(&new_str, string[str_ind++]);
		if (!new_str)
			return NULL;
	}
	return new_str;
}

int	var_already_there(t_env **minish_envp, t_env **minish_local_var, char *next_var)
{
	t_env *travel_var;

	travel_var = *minish_envp;
	while(travel_var)
	{
		if(ft_strncmp((travel_var)->VAR, next_var, ft_strlen(travel_var->VAR) == 0))
		return(2);
		travel_var = travel_var->next;
	}
	if(minish_local_var != NULL && *minish_local_var != NULL)
	{
		travel_var = *minish_local_var;
		while(travel_var)
		{
			if(ft_strncmp((travel_var)->VAR, next_var, ft_strlen(travel_var->VAR) == 0))
				return(1);
			travel_var = travel_var->next;
		}
	}
	return(0);
}
