#include "../inc/minishell.h"

int env_list_length(t_env *traveler)
{
    int count = 0;

    while (traveler != NULL)
    {
        count++;
        traveler = traveler->next;
    }
    return count;
}
int	remove_env_var(t_env **head, const char *var)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->VAR, var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->VAR);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
t_env *find_first(t_env *envp)

{
	t_env	*min;

	if (!envp)
		return (NULL);
	min = envp;
	envp = envp->next;
	while (envp)
	{
		if (ft_strcmp(envp->VAR, min->VAR) < 0)
			min = envp;
		else if (ft_strcmp(envp->VAR, min->VAR) == 0)
		{
			if (ft_strcmp(envp->value, min->value) < 0)
				min = envp;
		}
		envp = envp->next;
	}

	return (min);
}
int	is_between_env(t_env *envp, t_env *smallest, t_env *bigger)
{
	int	cmp_small;
	int	cmp_big;

	if (!envp || !smallest || !bigger)
		return (-1);
	cmp_small = ft_strcmp(envp->VAR, smallest->VAR);
	cmp_big = ft_strcmp(envp->VAR, bigger->VAR);
	if (cmp_small > 0 && cmp_big < 0)
		return (0);
	if (cmp_small == 0)
	{
		if (ft_strcmp(envp->value, smallest->value) > 0)
			return (0);
	}
	if (cmp_big == 0)
	{
		if (ft_strcmp(envp->value, bigger->value) < 0)
			return (0);
	}
	return (-1);
}
t_env	*create_env_node(char *var, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->VAR = strdup(var);
	new->value = strdup(value);
	new->next = NULL;
	return (new);
}

int	add_env_back(t_env **env_list, char *var, char *value)
{
	t_env	*new;
	t_env	*temp;

	if (!env_list || !var || !value)
		return (-1);
	new = create_env_node(var, value);
	if (!new)
		return (-1);
	if (*env_list == NULL)
	{
		*env_list = new;
		return (0);
	}
	temp = *env_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int update_env_value(t_env *env_list, const char *var_name, const char *new_value)
{
    t_env *current;

	current = env_list;
    while (current)
    {
        if (ft_strcmp(current->VAR, var_name) == 0)
        {
            if (current->value)
                free(current->value);
            current->value = ft_strdup(new_value);
            if (current->value == NULL)
				return -1; // Memory allocation failed
			return 0; // Successfully updated the value
        }
        current = current->next;
    }
	return 1;
}
char	**env_list_to_array(t_env *env, int len)
{
	char	**env_array;
	int		i;

	if (len <= 0)
		return (NULL);
	env_array = malloc(sizeof(char *) * (len + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env && i < len)
	{
		env_array[i] = join_var_value(env->VAR, env->value);
		if (!env_array[i])
		{
			free_tab(env_array);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
char *join_var_value(char *var, char *value)
{
	char *result;
	size_t len;

	len = strlen(var) + 1 + strlen(value) + 1;
	result = malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, var, strlen(var));
	ft_strlcat(result, "=", strlen(value) + 1);
	ft_strlcat(result, value, len);
	return (result);
}