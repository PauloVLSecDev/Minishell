/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/11 12:47:49 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], char *envp[])
{
	t_token	*token;
	t_token	*token_list;
	t_cmd	*cmd;
	char	*input;
	t_env	*env_copy;
	char	**path;

	(void)argc;
	(void)argv;
    
	env_copy = linked_node_env(envp);
	token = NULL;
	(void)path;
	while (1)
	{
		input = readline("minishell> ");
       // if (!*input)
       //     return (0);
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
		cmd = token_to_cmd(token_list);
		execution_cmd(env_copy, cmd);
		ft_print_token(token_list);
		free_token_list(token_list);
		free_cmd(cmd);
		free(input);
	}
	return (0);
}
