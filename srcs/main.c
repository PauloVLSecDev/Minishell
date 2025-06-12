/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/12 19:54:59 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[],
		char *envp[])
{
	t_shell	*sh;

	sh = malloc(sizeof(t_shell));
	if (!sh)
		return (1);
	sh->env = linked_node_env(envp);
	sh->cmd = NULL;
	sh->token = NULL;
	sh->input = NULL;
	while (1)
	{
		sh->input = readline("minishell> ");
		if (!sh->input || !*sh->input)
		{
			free(sh->input);
			continue;
		}
		if (!check_quotes(sh->input))
			ft_printf("nao contem um numero par de aspas: %s\n", sh->input);
		add_history(sh->input);
		sh->token = tokenization(sh->token, sh->input);
		valid_pipe(sh->token);
		valid_redir_in(sh->token);
		valid_redir_out(sh->token);
		valid_heredoc(sh->token);
		token_to_cmd(sh);
		execution_cmd(sh);
		ft_print_token(sh->token);
		free_token_list(sh->token);
		free_cmd(sh->cmd);
		free(sh->input);
		sh->token = NULL;
		sh->cmd = NULL;
		sh->input = NULL;
	}
	return (0);
}
