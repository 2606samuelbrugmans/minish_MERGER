/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:45:41 by scesar            #+#    #+#             */
/*   Updated: 2025/07/15 17:45:44 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *get_curr_path(t_env **envp)
{
	char cwd[PATH_MAX];
	char *path;
	char *home;
	char *temp;

	home = get_VAR(envp, NULL, "HOME")->value;
	if(!home)
		return(NULL);
	if(!getcwd(cwd, sizeof(cwd)))
		return(NULL);			//handle error ?
	path = ft_strdup("~");
	if(!path)
		return(NULL);		//malloc error
	temp = ft_strjoin(path, cwd + ft_strlen(home));
	free(path);
	if(!temp)
		return(NULL);		//malloc error
	path = ft_strjoin(temp, ": ");
	free(temp);
	if(!path)
		return(NULL);		//malloc error
	return(path);
}

char *get_prompt(t_env **envp)
{
	t_env *user_var;
	char *prompt;
	char *user;
	char *temp;
	char *path;

	user_var = get_VAR(envp, NULL, "USER");
	if(!user_var || !user_var->value)
		return(NULL);			//handle error ?
	if(!user_var || !user_var->value)
		user = ft_strdup("user :");
	else
		user = ft_strjoinchar(user_var->value, ':');
	if(!user)
		return(NULL);		//malloc error
	path = get_curr_path(envp);
	if(!path)
		return(free(user), NULL);		//malloc error;
	temp = ft_strjoin("minishell@", user);
	if(!temp)
		return(free(user),free(path),NULL);		//malloc error;
	prompt = ft_strjoin(temp, path);
	return(free(user), free(temp),free(path), prompt);
}
