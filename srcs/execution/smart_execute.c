/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:05:05 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/13 18:05:08 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	smart_execute(t_cmd *cmd)
{
	char	**new_env;
	char	**path;

	path = NULL;
	new_env = NULL;
	if (cmd->next == NULL)
	{
		if (is_builtin(cmd->args) != -1)
			exec_builtin(is_builtin(cmd->args), cmd);
		else
			exec_single_command(cmd, new_env, path);
	}
	else if (cmd->next != NULL)
		execute_pipeline(cmd);
	else
		return ;
}

void	exec_single_command(t_cmd *cmd, char **new_env, char **path)
{
	pid_t	pid;
	int		status;

	expand_all_args(cmd, get_shell()->env);
	path = find_path(get_shell()->env);
	new_env = recreate_env(get_shell()->env);
	if (!path)
	{
		free_env(get_shell()->env);
		cleanup_iteration();
		exit(get_shell()->exit_status = 1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (redir_actions(cmd))
		{
			free_all(path);
			free_env(get_shell()->env);
			free_all(new_env);
			perror("");
			cleanup_iteration();
			exit(2);
		}
		exec_external(cmd, new_env, path);
		free_all(new_env);
		cleanup_iteration();
		if (get_shell()->exit_status == 127)
			exit(127);
		else
			exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		get_shell()->exit_status = WEXITSTATUS(status);
	}
	free_all(path);
	free_all(new_env);
}
