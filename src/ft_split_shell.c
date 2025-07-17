#include "../inc/minishell.h"


//watch out to tab !! I don't take those in consideration at all
size_t end_quotes(char *input, size_t *index)
{
	char quote;
	size_t  size;

	size = 0;
	quote = input[*index];
	(*index)++;
	while (input[*index] && input[*index] != quote)
	{
		size++;
		(*index)++;
	}
	if (input[*index] != quote) //if it does not end quotes (for later)
		return(0);
	if (input[*index] == quote)
		(*index)++;
	return(size + 2); //count quotes
}

void free_tab(char **tab)
{
	size_t i;

	i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

size_t next_arg_len(char *input, size_t input_index)
{

	size_t len;
	size_t index;

	len = 0;
	index = input_index;
	// printf("input : %s\n", input);
	// printf("index before : %ld\n", index);
	if (special_symb(input, input_index) != NONE)
	{
		if(special_symb(input, index) == HEREDOC || special_symb(input, index) == APPEND)
			return(2);
		else
			return(1);
	}
	while(input[index])
	{
		if(input[index] == '\'' || input[index] == '\"')
		{
			len += (end_quotes (input, &index));
		}
		else if (input[index] == ' ' || (special_symb(input, index) != NONE))
			break;
		else
		{
			index ++;
			len++;
		}
	}
	// printf("index after : %ld\n", index);
	// printf("len : %ld\n", len);
	// exit(1);
	return (len);
}
	// size_t len;
	// int start_of_quotes;
	// char quotes_type;
	// char *quotes;
	// char *temp;

	// len = 0;
	// if (special_symb(input[input_index]))
	//	 return (1);
	// if (input[input_index] == '\'' || input[input_index] == '\"')
	// {
	//	 quotes_type = input[input_index];
	//	 start_of_quotes = (int) input_index;
	//	 end_quotes(input, input_index);
	//	 quotes = ft_substr(input, start_of_quotes, input_index - start_of_quotes);
	//	 temp = ft_delchar(quotes, quotes_type);
	//	 free(quotes);
	//	 len = next_arg_len(temp, 0);
	// }
	// else
	//	 while (input[input_index] && input[input_index] != ' ' && (!special_symb(input[input_index])))
	//	 {
	//		 len++;
	//		 input_index++;
	//	 }
	// return(len);


int	put_elem_in_tab(char **tab, size_t tab_index, char *input, size_t *input_index)
{
	char *elem;
	size_t elem_size;
	size_t elem_index;
	size_t before_quote_index;
	char quote;

	elem_index = 0;
	elem_size = next_arg_len(input, *input_index) + 1;
	elem = malloc(sizeof(char) * elem_size);
	if (!elem)
		return(0);				 //need to handle malloc error
	while(elem_index < elem_size - 1)
	{
		if(input[*input_index] == '\'' || input[*input_index] == '\"')
		{
			quote = input[*input_index];
			elem[elem_index++] = quote;      //
			(*input_index)++;
			while(input[*input_index] && input[*input_index] != quote)
				elem[elem_index++] = input[(*input_index)++];
			if (input[*input_index] == quote)
			{
				elem[elem_index++] = quote;
				(*input_index) ++;
			}
		}
		else
			elem[elem_index++] = input[(*input_index)++];
	}
	elem[elem_index] = '\0';
	tab[tab_index] = elem;
	// printf("elem : %s\n", elem);
	// printf("elem_size : %ld\n", elem_size);
	// exit(1);
	return(1);
}

size_t nbr_of_elem(char *input)
{
	size_t index;
	size_t nbr;

	index = 0;
	nbr = 0;
	while(input[index])
	{
		while(input[index] == ' ')
			index++;
		if (special_symb(input, index) != NONE)
		{
			if(special_symb(input, index) == HEREDOC || special_symb(input, index) == APPEND)
				index +=2;
			else
				index +=1;
		}
		else
		{
			while (input[index] && input[index] != ' ' && special_symb(input, index) == NONE)
			{
				if (input[index] == '\'' || input[index] == '\"')
				{
					end_quotes(input, &index);  //have to wait if we don't have an ending quote
				}
				else
					index++;
			}
		}
		if (input[index] || (index > 0 && input[index - 1] != ' ')) //checks if the line finishes with spaces or if we reached the end
			nbr++;
		// printf("nbr : %lu\n", nbr);
	}
	// exit(1);
	return(nbr);
}

char **ft_split_shell(char *input)
{
	size_t	input_index;
	size_t	tab_index;
	size_t	tab_size;
	char **tab_of_elem;

	if(!input)
		return(NULL);
	tab_index = 0;
	input_index = 0;
	tab_size = nbr_of_elem(input) + 1;
	tab_of_elem = malloc(sizeof(char *) * (tab_size));
	if(!tab_of_elem)
		return (NULL);				 //malloc error
	while (tab_index < tab_size - 1)
	{
		while(input[input_index] == ' ')
			input_index++;
		if (input[input_index] != '\0')
		{
			if(!put_elem_in_tab(tab_of_elem, tab_index, input, &input_index))
			{
				free_tab(tab_of_elem);
				return(NULL);
			}
		}
		tab_index++;
	}
	tab_of_elem[tab_index] = NULL;
	// printf("tab_size : %ld\n", tab_size);
	// while (tab_of_elem[i])
	// {
	//	 printf("elem_%i : %s\n", i, tab_of_elem[i]);
	//	 i++;
	// }
	// exit(1);
	// while (tab_of_elem[i])
	// {
	// 	printf("tab_of_elem[i] : %s\n", tab_of_elem[i]);
	// 	i++;
	// }

	return (tab_of_elem);
}
