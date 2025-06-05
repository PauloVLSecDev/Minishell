/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/05 20:02:17 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char *argv[], char *envp[]) 
{
    (void) argc;
    (void)argv;

	t_token	*token;
	t_token	*token_list;
	char	*input;
    t_env *env_copy;

    env_copy = insertion_node_end_in_env(envp);
	token = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!check_quotes(input))
			ft_printf("nao contem um numero par de aspas: %s\n", input);
		if (!ft_strcmp(input, "exit"))
		{
			free(input);
            free_env(env_copy);
			return (1);
		}
		add_history(input);
		token_list = tokenization(token, input);
		valid_pipe(token_list);
		valid_redir_in(token_list);
		valid_redir_out(token_list);
		valid_heredoc(token_list);
		ft_print_token(token_list);
		free(input);
	}
	return (0);
}
