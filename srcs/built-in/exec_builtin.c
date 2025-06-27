/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/27 17:40:46 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **args)
{
	if (!args || !*args || !args[0])
		return (-1);
	if (!ft_strcmp(args[0], "echo"))
		return (ECHO);
	if (!ft_strcmp(args[0], "pwd"))
		return (PWD);
	if (!ft_strcmp(args[0], "cd"))
		return (CD);
	if (!ft_strcmp(args[0], "env"))
		return (ENV);
	if (!ft_strcmp(args[0], "exit"))
		return (EXIT);
	return (-1);
}

int exec_builtin(int code, t_cmd *cmd)
{
    if (code == ECHO)
        ft_echo(cmd->args);
    else if (code == PWD)
        ft_pwd();
    else if (code == CD)
        ft_cd(cmd->args);
    else if (code == ENV)
        ft_env(cmd->args);
    else if (code == EXIT)
        ft_exit(cmd->args);
    return (code);
}
