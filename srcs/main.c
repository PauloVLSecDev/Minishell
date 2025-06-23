/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/23 13:31:27 by brunogue         ###   ########.fr       */
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
		if (!sh->input) 
        {
            printf("exit\n");
            clean_exit(sh, 0);
            break ; 
        }
        if (!*sh->input)
        {
            free(sh->input);
            continue;
        }
		if (!check_quotes(sh->input))
        {
			ft_printf("nao contem um numero par de aspas: %s\n", sh->input);
            free(sh->input);
            sh->input = NULL;
            continue ;
        }
		add_history(sh->input);
		sh->token = tokenization(sh->token, sh->input);
//		valid_pipe(sh->token);
//		valid_redir_in(sh->token);
//		valid_redir_out(sh->token);
//		valid_heredoc(sh->token);
		token_to_cmd(sh);
		exec_all(sh);
		ft_print_token(sh->token);
        cleanup_iteration(sh);
		sh->token = NULL;
		sh->cmd = NULL;
		sh->input = NULL;
	}
	return (0);
}
