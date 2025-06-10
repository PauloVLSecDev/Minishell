/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/10 17:47:40 by brunogue         ###   ########.fr       */
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
	token = NULL;
	(void)path;
	env_copy = linked_node_env(envp);
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
		cmd = token_to_cmd(token_list);
		//execution_cmd(env_copy, cmd);
		exec_builtin(cmd, env_copy);
		ft_printf("asffsd %s\n", get_env_value(env_copy, "OLDPWD"));
		ft_print_token(token_list);
		free_token_list(token_list);
		free_cmd(cmd);
		free(input);
	}
	return (0);
}
