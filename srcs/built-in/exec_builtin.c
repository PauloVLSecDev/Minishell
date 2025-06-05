/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/05 19:09:19 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *input)
{
	if (!input)
		return (-1);
	if (!ft_strcmp(input, "echo"))
		return (ECHO);
	if (!ft_strcmp(input, "pwd"))
		return (PWD);
	return (-1);
}

int	exec_builtin(t_cmd *cmd)
{
	int	code;

	code = is_builtin(cmd->args[0]);
	if (code == ECHO)
		ft_echo(cmd->args);
	if (code == PWD)
		ft_printf("PWD");
	return (1);
}

t_cmd	*token_to_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	int i;
	
	
}
