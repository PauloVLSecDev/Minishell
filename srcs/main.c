/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/23 14:37:05 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[],
		char *envp[])
{
    t_env *new_envp;
    char *input;

    new_envp = linked_node_env(envp);
    init_shell(new_envp);
    input = get_shell()->input;
	while (1)
	{
	    input = readline("minishell> ");
		if (!input) 
        {
            printf("exit\n");
            clean_exit(0);
            break ; 
        }
        if (!*input)
        {
            free(get_shell()->input);
            continue;
        }
		if (!check_quotes(input))
        {
			ft_printf("nao contem um numero par de aspas: %s\n", input);
            free(input);
            input = NULL;
            continue ;
        }
		add_history(input);
		get_shell()->token = tokenization(get_shell()->token, input);
//		valid_pipe(sh->token);
//		valid_redir_in(sh->token);
//		valid_redir_out(sh->token);
//		valid_heredoc(sh->token);
		token_to_cmd();
		exec_all();
//	    ft_print_token(get_shell()>token);
        cleanup_iteration();
	}
	return (0);
}

t_shell *get_shell()
{
    static t_shell minishell; 

    return (&minishell);
}

void    init_shell(t_env *envp)
{
    get_shell()->input = NULL;
	get_shell()->env = envp;
	get_shell()->cmd = NULL;
	get_shell()->token = NULL;
	get_shell()->exit_status = 0;
	get_shell()->input = NULL;
}	

