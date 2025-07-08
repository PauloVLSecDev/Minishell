/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:05:18 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/08 14:51:00 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[],
		char *envp[])
{
	t_env	*new_envp;
	t_token	*current;
	char	*input;

	current = NULL;
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
			continue ;
		}
		if (!check_quotes(input))
		{
			ft_printf("used "" or '' don´t %s\n",input);
			free(input);
			continue ;
		}
		add_history(input);
		get_shell()->token = tokenization(get_shell()->token, input, current);
		free(input);
		ft_print_token(get_shell()->token);
		if (valid_metacharacteres(get_shell()->token))
		{
			//free_env(get_shell()->env);	
			cleanup_iteration();
			get_shell()->exit_status = 2;
			continue ;
		}
		ft_print_token(get_shell()->token);
		handle_command(get_shell()->token);
		smart_execute(get_shell()->cmd);
		cleanup_iteration();
	}
	return (0);
}

t_shell	*get_shell(void)
{
	static t_shell	minishell;

	return (&minishell);
}

void	init_shell(t_env *envp)
{
	get_shell()->input = NULL;
	get_shell()->env = envp;
	get_shell()->cmd = NULL;
	get_shell()->token = NULL;
	get_shell()->exit_status = 0;
	get_shell()->input = NULL;
}
