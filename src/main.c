/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/17 17:03:54 by scesar			#+#	#+#			 */
/*   Updated: 2025/06/25 12:38:17 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minishell.h"

int treat_input(t_minishell **minish, char *input)
{
	t_commands *cmd_as_tokens;

	if(!input || *input == '\0')
		return(1);
	if(!first_check(input))
		return(3);
	if(add_loc_var(&(*minish)->envp,&(*minish)->local_var, input))
		return(1);
	(*minish)->parsed_string = get_new_string(**minish, input);
	printf("parsed_string : |%s|\n", (*minish)->parsed_string);
	if(!(*minish)->parsed_string)
		return(0);		//handle error
	cmd_as_tokens = tokenizer((*minish)->parsed_string);
	if(!cmd_as_tokens)
		return(3);		//handle errors
	(*minish)->number_of_commands = count_commands(cmd_as_tokens);
	(*minish)->instru = init_insrtu((*minish), cmd_as_tokens);
	if (!(*minish)->instru)
		return(0);		//handle errors or empty inputs
	//need to free cmd_as_tokens_here
	(*minish)->fd_pipes = malloc(sizeof(int[2]) * ((*minish)->number_of_commands));
	if (!(*minish)->fd_pipes)
		return (0);
	run(*minish);
	return (1);
}

void	init_minish(t_minishell **minish, char **envp)
{
	(*minish) = malloc(1 * sizeof(t_minishell));
	(*minish)->envp = NULL;
	(*minish)->local_var = NULL;
	(*minish)->instru = NULL;
	(*minish)->number_of_commands = 0;
	(*minish)->fd_pipes = NULL;
	(*minish)->last_exit_status = 0;
	if(!set_envp(&(*minish)->envp, envp))
		exit_shell("Something went wrong while setting env\n", (*minish));
}

int	main(int ac, char **av, char **envp)
{
	t_minishell		*minish;
	char *prompt;
	char *input;

	init_minish(&minish, envp);
	setup_signals();
	while(1)
	{
		prompt = get_prompt(&minish->envp);
		if(!prompt)
			break;
		input = readline(prompt);
		free(prompt);
		if(!input)
			break;
		if (input && *input) 
    		add_history(input);		
		if (treat_input(&minish, input) == 3)
			minish->last_exit_status = 2;
		free(input);
	}
	free_minish(&minish);
	return(0);
}


// int treat_input(t_minishell **minish, char *input)
// {
// 	t_commands *cmd_as_tokens;

// 	if(!input || *input == '\0')
// 		return(1);
// 	if(!first_check(input))
// 		return(0);
// 	if(add_loc_var(&(*minish)->envp,&(*minish)->local_var, input))
// 		return(1);
// 	// t_env *travel = (*minish)->local_var;
// 	// int i = 0;
// 	// while(travel)
// 	// {
// 	// 	printf("var [%d] : %s=%s\n", i, travel->VAR, travel->value);
// 	// 	i++;
// 	// 	travel = travel->next;
// 	// }
// 	(*minish)->parsed_string = get_new_string(**minish, input);
// 	if(!(*minish)->parsed_string)
// 		return(0);		//handle error
// 	cmd_as_tokens = tokenizer((*minish)->parsed_string);
// 	if(!cmd_as_tokens)
// 		return(0);		//handle errors
// 	(*minish)->number_of_commands = count_commands(cmd_as_tokens);
// 	(*minish)->instru = init_insrtu((*minish), cmd_as_tokens);

	// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// // for you to test, but a bit wierd, I'l simplify things and explain you also
	// size_t i = 0;
	// while(i < (*minish)->number_of_commands)
	// {
	// 	t_instructions instr = (*minish)->instru[i];
	// 	printf("---------------------------------\n");
	// 	printf("		instr		\n");
	// 	printf("---------------------------------\n");
	// 	printf("whole command : |%s|\n", instr.command);
	// 	size_t j = 0;
	// 	while(instr.executable[j])
	// 	{
	// 		printf("executable : %s | type : %d\n", instr.executable[j]->content, instr.executable[j]->type);
	// 		j++;
	// 	}
	// 	t_redir *in = instr.in_redir;
	// 	if(!in)
	// 		printf("NO REDIR_IN\n");

	// 	else
	// 	{
	// 		int in_index = 0;
	// 		while(in[in_index].file_name)
	// 		{
	// 			printf("redir_in : |file=%s|, |type=%d|\n", in[in_index].file_name, in[in_index].type);
	// 			in_index++;
	// 		}
	// 	}
	// 	t_redir *out = instr.out_redir;
	// 	if(!out)
	// 		printf("NO REDIR_OUT\n");

	// 	else
	// 	{
	// 		int out_index = 0;
	// 		while(out[out_index].file_name)
	// 		{
	// 			printf("redir_out : |file=%s|, |type=%d|\n", out[out_index].file_name, out[out_index].type);
	// 			out_index++;
	// 		}
	// 	}
	// 	i++;
	// }
	// exit(1);
	// ///////////////////////////////////////////////////////////////////////////////////////////////////////////

// 	// free_commands(cmd_as_tokens);
// 	//need to free cmd_as_tokens_here
// 	if (!(*minish)->instru)
// 		return(0);		//handle errors or empty inputs
// 	return (1);
// }
