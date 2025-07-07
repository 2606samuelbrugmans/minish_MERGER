/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:51:19 by scesar            #+#    #+#             */
/*   Updated: 2025/06/30 21:40:28 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	run_command(char **tab_input)
{
	pid_t   pid;
	int status;

	if (!tab_input || !tab_input[0])
		return;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		if (execve(tab_input[0], tab_input, NULL) == -1)
		{
			perror("execve");
			return;
		}
	}
	else
		waitpid(pid, &status, 0);
}

char *ft_delchar(char *str, char to_del)
{
	//need to free str after (using a temp before calling fct)
	size_t index;
	size_t index_res;
	size_t new_size;
	char *res;

	index = 0;
	index_res = 0;
	new_size = ft_strlen(str) - ft_countchar(str, to_del) + 1;
	res = malloc(sizeof(char) * new_size);
	if (!res)
		return(NULL);
	while (str[index])
	{
		if(str[index] != to_del)
		{
			res[index_res] = str[index];
			index_res ++;
		}
		index ++;
	}
	res[index_res] = '\0';
	return(res);
}

size_t ft_countchar(char *str, char to_count)
{
	size_t res;
	size_t index;

	res = 0;
	index = 0;
	while(str[index])
	{
		if (str[index] == to_count)
			res++;
		index++;
	}
	return (res);
}

size_t tab_size(char **tab)
{
	size_t index;

	index = 0;

	while (tab[index])
		index++;
	return(index);
}

int special_symb(char *input, size_t index)
{

	if (input[index] == '<' )
	{
		if(input[index + 1] && input[index + 1] == '<' )
			return(HEREDOC);
		else
			return (REDIR_IN);
	}
	else if(input[index] == '>' )
	{
		if(input[index + 1] && input[index + 1] == '>')
			return(APPEND);
		else
			return (REDIR_OUT);
	}
	if(input[index] == '|' ) //put strcmp ? bc compare a char to a char*
		return(PIPE);
	else
		return(NONE);
}

int special_symb_2(char *input)
{
	size_t len;

	len = ft_strlen(input);
	if (ft_strncmp(input, "<", len) == 0)
		return (REDIR_IN);
	if (ft_strncmp(input, ">", len) == 0)
		return (REDIR_OUT);
	if (ft_strncmp(input, ">>", len) == 0)
		return (APPEND);
	if (ft_strncmp(input, "<<", len) == 0)
		return (HEREDOC);
	if (ft_strncmp(input, "|", len) == 0)
		return (PIPE);
	else
		return(NONE);
}

char *ft_strjoinchar(char *str, char c)
{
	char *new_str;
	char temp[2];

	temp[0] = c;
	temp[1] = '\0';
	new_str = ft_strjoin(str, temp);
	// if(str)
	//	 free(str);
	return(new_str);
}

int	count_commands(t_commands *cmd_as_token)
{
	int count;
	t_commands *travel;

	count = 0;
	travel = cmd_as_token;
	while(travel)
	{
		count++;
		travel = travel->next_command;
	}
	return(count);
}

int count_redir(t_commands **cmd_as_token, t_token_type redir_type)
{
	size_t index;
	int count;
	t_token **travel;

	index = 0;
	count = 0;
	travel = (*cmd_as_token)->args;
	while(travel[index])
	{
		if(redir_type == REDIR_IN)
		{
			if (travel[index]->type == REDIR_IN || travel[index]->type == HEREDOC)
				count++;
		}
		else if(redir_type == REDIR_OUT)
		{
			if (travel[index]->type == REDIR_OUT || travel[index]->type == APPEND)
				count++;
		}
		index ++;
	}
	return(count);
}

int ft_is_number(const char *str)
{
	int i = 0;

	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}