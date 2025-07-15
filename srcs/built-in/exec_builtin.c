/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/14 20:41:57 by pvitor-l         ###   ########.fr       */
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
	if (!ft_strcmp(args[0], "export"))
		return (EXPORT);
	if (!ft_strcmp(args[0], "unset"))
		return (UNSET);
	if (!ft_strcmp(args[0], "exit"))
		return (EXIT);
	return (-1);
}

int	exec_builtin(int code, t_cmd *cmd)
{
	t_fd_backup	backup;

	backup_fds(&backup);
	if (redir_actions(cmd))
	{
		perror("");
		restaure_for_origin_fds(&backup);
		return (-1);
	}
	if (code == ECHO)
		get_shell()->exit_status = ft_echo(cmd->args);
	else if (code == PWD)
		get_shell()->exit_status = ft_pwd();
	else if (code == CD)
		get_shell()->exit_status = ft_cd(cmd->args);
	else if (code == ENV)
		get_shell()->exit_status = ft_env(cmd->args);
	else if (code == EXPORT)
		get_shell()->exit_status = ft_export(cmd->args);
	else if (code == UNSET)
		get_shell()->exit_status = ft_unset(&(get_shell()->env), cmd->args);
	else if (code == EXIT)
	{
		restaure_for_origin_fds(&backup);
		close_fds(&backup);
		get_shell()->exit_status = ft_exit(cmd->args);
	}
	restaure_for_origin_fds(&backup);
	close_fds(&backup);
	return (get_shell()->exit_status);
}
