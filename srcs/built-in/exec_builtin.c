/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/26 21:32:24 by pvitor-l         ###   ########.fr       */
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

int	fds_error(t_fd_backup *backup, t_cmd *cmd)
{
	backup_fds(backup);
	if (redir_actions(cmd))
	{
		perror("");
		restaure_for_origin_fds(backup);
		close_fds(backup);
		get_shell()->exit_status = 1;
		return (-1);
	}
	restore_and_close(backup);
	return (0);
}

int	exec_builtin(int code, t_cmd *cmd, t_env *env)
{
	t_shell	*shell;

	shell = get_shell();
	if (fds_error(shell->backup_fds, cmd))
		return (-1);
	if (code == ECHO)
		shell->exit_status = ft_echo(cmd->args);
	else if (code == PWD)
		shell->exit_status = ft_pwd();
	else if (code == CD)
		shell->exit_status = ft_cd(cmd->args);
	else if (code == ENV)
		shell->exit_status = ft_env(cmd->args);
	else if (code == EXPORT)
		shell->exit_status = ft_export(cmd->args);
	else if (code == UNSET)
		shell->exit_status = ft_unset(&env, cmd->args);
	else if (code == EXIT)
		shell->exit_status = ft_exit(cmd->args);
	restore_and_close(shell->backup_fds);
	return (shell->exit_status);
}

void	restore_and_close(t_fd_backup *backup)
{
	restaure_for_origin_fds(backup);
	close_fds(backup);
}
