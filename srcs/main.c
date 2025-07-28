/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:05:18 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/28 18:39:14 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_valid_token_and_mcharacteres(t_token *token);

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
	t_token	*aux_node;
	t_token	*tmp_node;
	char	*input;

	aux_node = NULL;
	tmp_node = NULL;
	new_envp = linked_node_env(envp);
	init_shell(new_envp);
	while (1)
	{
		signals_ctrl_c();
		input = readline("minishell> ");
		add_history(input);
		if (!verify_input(input))
			continue ;
		tmp_node = tokenization(get_shell()->token, input, aux_node);
		get_shell()->token = tmp_node;
		ft_print_token(get_shell()->token);
		if (double_valid_token_and_mcharacteres(get_shell()->token))
			continue ;
		handle_command(get_shell()->token);
		smart_execute(get_shell()->cmd);
		cleanup_iteration();
	}
	return (0);
}

static int	double_valid_token_and_mcharacteres(t_token *token)
{
	if (!token || valid_metacharacteres(token))
	{
		cleanup_iteration();
		return (1);
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
	t_fd_backup	backup;

	get_shell()->env = envp;
	get_shell()->cmd = NULL;
	get_shell()->token = NULL;
	get_shell()->backup_fds = &backup;
	get_shell()->exit_status = 0;
	get_shell()->must_execute = 0;
	get_shell()->heredoc_counter = -1;
}
