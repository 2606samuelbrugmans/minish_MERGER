/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:01:27 by scesar            #+#    #+#             */
/*   Updated: 2025/07/01 21:08:10 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*path_finding(char *pathed, t_env **envp)
{
	t_env		*path;
	char	*full_path;

	if (ft_strchr(pathed, '/'))					//covers full path
	{
		if (access(pathed, X_OK) == 0)
			return (ft_strdup(pathed));
		else
			return (NULL);
	}
	printf("pathed : %s\n", pathed);
	path = get_VAR(envp, NULL, "PATH");
	if (path == NULL)
		return (NULL);		//not sure we need to protect here
	// ft_putnbr_fd(path, 2);
	full_path = get_path(pathed, path->value, 5);
	if (full_path == pathed)		//if the path is not found, we return the original command
		return (NULL);
	return (full_path);
}

// char	*path_finding(char *pathed, char **env)
// {
// 	int		path;
// 	char	*full_path;

// 	path = find_string(env, "PATH");
// 	if (path == -1)
// 		return (NULL);
// 	ft_putnbr_fd(path, 2);
// 	full_path = get_path(pathed, env[path], 5);
// 	return (full_path);
// }

char	*potential_pathing(char *paths, char *command_to_path, int *index)
{
	char	*potential_path;
	int		size;

	size = path_len(paths, *index);
	size += strlen(command_to_path);
	potential_path = malloc((size + 2) * sizeof(char));
	if (potential_path == NULL)
		return (NULL);
	potential_path[size + 1] = '\0';
	size = 0;
	while (paths[*index] != '\0' && paths[*index] != ':')
	{
		potential_path[size] = paths[*index];
		size++;
		(*index)++;
	}
	if (paths[*index] == ':')
		(*index)++;
	potential_path[size] = '/';
	size++;
	putcommand(command_to_path, potential_path, size);
	return (potential_path);
}

int	find_string(char **env, char *path)
{
	int	index;
	int	index_two;

	index = 0;
	index_two = 0;
	while (env[index][index_two] != '\0' && env[index][index_two] != '=')
	{
		index_two = 0;
		while (path[index_two] != '\0'
			&& env[index][index_two] == path[index_two])
			index_two++;
		if (path[index_two] == '\0')
			return (index);
		index++;
	}
	return (-1);
}

char	*get_path(char *command_to_path, char *paths, int index)
{
	char	*full_path;

	if (command_to_path == NULL || command_to_path[0] == 32)
		return (NULL);
	while (paths[index] != '\0')
	{
		full_path = potential_pathing(paths, command_to_path, &index);
		printf("full_path : %s\n", full_path);
		printf("to_path : %s\n", command_to_path);

		if (access(full_path, X_OK) == 0)
			return (full_path);
		if (full_path != NULL)
			free(full_path);
	}
	return (NULL);
}
int	path_len(char *string, int index)
{
	int	second_index;

	second_index = 0;
	while (string[index + second_index] != '\0'
		&& string[index + second_index] != ':'
		&& string[index + second_index] != ' ')
		second_index++;
	return (second_index);
}

void	putcommand(char *command_to_path, char *potential_path, int size)
{
	int	j;

	j = 0;
	while (command_to_path[j] != '\0')
	{
		potential_path[size + j] = command_to_path[j];
		j++;
	}
}
