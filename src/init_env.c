/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_env.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/24 19:32:55 by scesar			#+#	#+#			 */
/*   Updated: 2025/06/24 19:44:44 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minishell.h"
int update_SHLVL(t_env **env)
{
	char *new_value;
	int level;

	ft_printf(" Updating SHLVL...\n");
	if (!(*env)->value)
		level = 0;
	else
		level = ft_atoi((*env)->value);
	if (level < 0)
		level = 0; // reset SHLVL if it is negative
	else if (level > 1000)
		level = 999; // cap SHLVL to 1000
	level++;
	printf("level : %d", level);
	printf("env-> var ; %s env> value; %s", (*env)->VAR, (*env)->value );
	new_value = ft_itoa(level);
	if (!new_value)
		return (0); // handle error
	free(((*env))->value);
	(*env)->value = new_value;
	return (1);
}


int	set_next_var(t_env **next_envv, char *envv, char *equal)
{
	if(!envv)		//check if works with VAR=	  like an empty value
		return(0);
	*next_envv = malloc(sizeof(t_env));								//need to free at the end
	if(!*next_envv)
		return(0);
	(*next_envv)->VAR = ft_substr(envv, 0, equal - envv);
	if (!(*next_envv)->VAR )
		return(0);
	(*next_envv)->value = ft_strdup(equal + 1);
	if (ft_strcmp((*next_envv)->VAR, "SHLVL") == 0)
		return (update_SHLVL(next_envv));	//update SHLVL if it is set
	if (!(*next_envv)->value)
	{
		free((*next_envv)->value);
		free(*next_envv);
		return(0);					//handle errors
	}
	return(1);
}

t_env	*set_envp(t_env **minish_env, char **envp)
{
	size_t i;
	char *equal_is_there;
	t_env *current_envv;
	t_env *next_envv;

	i = 0;
	current_envv = NULL;
	next_envv = NULL;
	while (envp[i])
	{

		equal_is_there = ft_strchr(envp[i], '=');
		if (!equal_is_there)
		{
			i++;
			continue;
		}

		if (!set_next_var(&next_envv, envp[i], equal_is_there))
			return (NULL);
		if (*minish_env == NULL)
			*minish_env = next_envv;
		else
			current_envv->next = next_envv;
		current_envv = next_envv;
		i++;
	}
	if (current_envv)
		current_envv->next = NULL;
	printf("[DEBUG] Environment setup completed.\n");
	return(*minish_env);
}

t_env *get_VAR(t_env **minish_envp, t_env **minish_local_var, char *VAR)
{
	t_env *travel_var;

	if(!VAR)
		return(NULL);
	travel_var = *minish_envp;
	while (travel_var)
	{
		if (ft_strcmp(travel_var->VAR, VAR) == 0)
			return travel_var;
		travel_var = travel_var->next;
	}
	if(minish_local_var != NULL && *minish_local_var != NULL)
	{
		travel_var = *minish_local_var;
		while (travel_var)
		{
			if(ft_strncmp((travel_var)->VAR, VAR, ft_strlen(travel_var->VAR)) == 0)
				return(travel_var);
			travel_var = travel_var->next;
		}
	}
	return(NULL);
}
// t_env	*set_envp(t_env **minish_env, char **envp)
// {
// 	size_t i;
// 	char *equal_is_there;
// 	t_env *current_env;
// 	t_env *next_envv;

// 	i = 0;
// 	current_env = NULL;
// 	next_envv = NULL;
// 	while(envp[i])
// 	{
// 		next_envv = malloc(sizeof(t_env));								//need to free at the end
// 		if(!next_envv)
// 			return(NULL);
// 		equal_is_there = ft_strchr(envp[i], '=');
// 		if(!equal_is_there)
// 		{
// 			free(next_envv);
// 			return(NULL);
// 		}
// 		next_envv->VAR = ft_substr(envp[i], 0, equal_is_there - envp[i]);
// 		next_envv->value = ft_strdup(equal_is_there + 1);
// 		if (!next_envv->VAR || !next_envv->value)
// 			return(NULL);					//handle errors
// 		if(*minish_env == NULL)
// 			*minish_env = next_envv;
// 		else
// 			current_env->next = next_envv;
// 		current_env = next_envv;
// 		i++;
// 	}
// 	current_env->next = NULL;
// 	return(*minish_env);
// }

