#include "../inc/minishell.h"


int	is_n_flag(const char *str)
{
	int i;

	if (!str || str[0] != '-')
		return (0);
	if (str[1] == '\0')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_n_flags(t_token **argv)
{
	int i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (is_n_flag(argv[i]->content))
			i++;
		else
			break;
	}
	return (i);
}
int is_builtin(char *cmd)
{
	return
	(
		ft_strcmp(cmd, "echo") == 0 ||	  //try with smth like echooo, or cd12,...
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0
	);
}

int built_in_parent(char *cmd)
{
	return
	(
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "exit") == 0
	);
}
int builtin_env(char **envp)
{
	int index;

	index = 0;
	while (envp[index] != NULL)
	{
		printf("%s\n", envp[index]);
		index++;
	}
	return (0);
}
int exec_builtin(t_token **executables, t_minishell *shell)
{

	if (!is_builtin(executables[0]->content))
		return (-1);
	if (ft_strcmp(executables[0]->content, "echo") == 0)
		return builtin_echo(executables);
	if (ft_strcmp(executables[0]->content, "pwd") == 0)
		return builtin_pwd();
	if (ft_strcmp(executables[0]->content, "exit") == 0 )
		return builtin_exit(executables);
	if (ft_strcmp(executables[0]->content, "unset") == 0 )
		return builtin_unset(executables, &shell->envp);
	if (ft_strcmp(executables[0]->content, "cd") == 0)
		return builtin_cd(executables[1]->content, shell);
	if (ft_strcmp(executables[0]->content, "env") == 0)
		return builtin_env(shell->envp);
	if (ft_strcmp(executables[0]->content, "export") == 0)
		return builtin_export(executables, shell);

	return (-1);
}
int builtin_echo(t_token **executables)
{
	int i;
	int j;
	int newline;

	i = 1;
	j = 1;
	newline = 1;
	i = check_n_flags(executables);
	if (i > 1)
		newline = 0;
	while (executables[i])
	{
		printf("%s", executables[i]->content);
		if (executables[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int builtin_cd(t_token **executables, t_minishell *minish)
{
	t_env *home_var;
	char *path;

	if (!executables[1])
	{
		home_var = get_VAR(&minish->envp, NULL, "HOME");
		if (home_var == NULL)
		{
			write(2, "bash: cd: HOME not set\n", 23);
			return (0);
		}
		else if (chdir(home_var->value) != 0)
		{
			perror("cd");
			return 1;
		}
	}
	else
		path = executables[1]->content;
	if (executables[2])
		write(2, "bash: cd: too many arguments", 29);
	else if (chdir(path) != 0)
	{
		perror("cd");
		return 1;
	}
	else 
		return 0;
	return 1;
}
int builtin_pwd(void)
{
	char cwd[500];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
	return 0;
}
t_env *find_nth(t_env *smallest, t_env *bigger, t_env *envp)
{
	int has_changed;

	has_changed = -1;
	while (envp)
	{
		if (is_between_env(envp, smallest, bigger) == 0)
			bigger = envp;
		envp = envp->next;
	}
	if (has_changed == -1)
		return (NULL);
	return (bigger);
}

 void print_declare(t_env *envp)
 {
	t_env	*smallest;
	t_env	*bigger;

	bigger = find_first(envp);
	if (bigger == NULL)
		return ;
	printf("declare -x %s%s\n", bigger->VAR, bigger->value);
	smallest = bigger;
	while (bigger != NULL)
	{
		printf("declare -x %s=%s\n", bigger->VAR, bigger->value);
		smallest = bigger;
		bigger = find_nth(smallest, bigger, envp);
	}
 }
int edit_env(char *content, t_minishell *minish)
{
	char	*equal_pos;
	char	*var;
	char	*value;

	equal_pos = ft_strchr(content, '=');
	if (equal_pos != NULL)
	{
		var = ft_substr(content, 0, equal_pos - content);
		if (var == NULL)
			return (-1);
		value = ft_substr(equal_pos + 1, 0, ft_strlen(equal_pos + 1));
		if (value == NULL)
			return (free(value), -1);
		remove_env_var(&minish->envp, var);
		if (get_VAR(&minish->local_var, NULL, var) != NULL)
			update_env_value(minish->envp, var, value);
		add_env_back(&minish->envp, var, value);
		free(var);
		free(value);
	}
	return (0);
}

int is_valid_identifier(const char *str)
{
    int i = 0;

    if (!str || !str[0])
        return 0;
    if (!(ft_isalpha(str[i]) || str[i] == '_'))
        return 0;
    i++;
    while (str[i] && str[i] != '=')
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return 0;
        i++;
    }

    return 1;
}
 int builtin_export(t_token **executables, t_minishell *minish)
 {
	int index;

	index = 1;
	if (executables[1] == NULL)
		 print_declare(minish->envp);
	else
	{
		while (executables[index])
		{
			if (!is_valid_identifier(executables[index]->content))
			{
				write(2, "bash: export: `", 15);
				write(2, executables[index]->content, ft_strlen(executables[index]->content));
				write(2, "': not a valid identifier\n", 27);
			}
			else if (ft_strchr(executables[index]->content, '=') != NULL)
				edit_env(executables[index]->content, minish);
			else if (get_VAR(&minish->envp, NULL, executables[index]->content) == NULL)
				add_env_back(&minish->envp, executables[index]->content, "");
			index++;
		}
	}
	return (0);
 }

int builtin_exit(t_token **executables)
{
	int exit_status;

	if (executables[1] == NULL)
		return (0);
	else if (executables[2] != NULL)
	{
		write(2, "bash: exit: too many arguments\n", 31);
		return (2);
	}
	else if (ft_is_number(executables[1]->content) == 0)
	{
		write(2, "bash: exit: ", 12);
		write(2, executables[1]->content, ft_strlen(executables[1]->content));
		write(2, ": numeric argument required\n", 28);
		exit_status = 255;
	}
	else
	{
		exit_status = atoi(executables[1]->content);
		if (exit_status < 0 || exit_status > 255)
			exit_status = exit_status % 256;
	}
	printf("exit %d\n", exit_status);
	return (exit_status);
}

 int builtin_unset(t_token **executables, t_env **envp)
 {
	int i = 1;
	while (executables[i])
	{
		remove_env_var(envp, executables[i]->content);
		i++;
	}
	return (0);
 }