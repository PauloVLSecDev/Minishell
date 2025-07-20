/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:05:18 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/20 16:12:54 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_input(char *input)
{
	if (!input)
	{
		printf("exit\n");
		clean_exit(0);
	}
	if (*input == '\0')
	{
		free(input);
		return (0);
	}
	if (!check_quotes(input))
	{
		ft_printf("used \"\" or '' don't %s\n", input);
		free(input);
		return (0);
	}
	return (1);
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[],
		char *envp[])
{
	t_env	*new_envp;
	char	*input;

	new_envp = linked_node_env(envp);
	init_shell(new_envp);
	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!verify_input(input))
			continue ;
		add_history(input);
		get_shell()->token = tokenization(get_shell()->token, input, NULL);
		if (!get_shell()->token)
		{
			cleanup_iteration();
			continue ;
		}
		if (valid_metacharacteres(get_shell()->token))
		{
			cleanup_iteration();
			get_shell()->exit_status = 2;
			continue ;
		}
		handle_command(get_shell()->token);
		// heredoc(get_shell()->token);
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
	get_shell()->env = envp;
	get_shell()->cmd = NULL;
	get_shell()->token = NULL;
	get_shell()->exit_status = 0;
}
