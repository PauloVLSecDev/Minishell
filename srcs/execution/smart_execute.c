/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:05:05 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/19 20:47:57 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	single_child_process(t_cmd *cmd, char **new_env, char **path);

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

	expand_all_args(cmd);
	path = find_path(get_shell()->env);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		get_shell()->exit_status = 1;
		cleanup_iteration();
		return ;
	}
	new_env = recreate_env(get_shell()->env);
	pid = fork();
	if (pid == 0)
		single_child_process(cmd, new_env, path);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		get_shell()->exit_status = WEXITSTATUS(status);
		free_all(path);
		free_all(new_env);
	}
}

static void	single_child_process(t_cmd *cmd, char **new_env, char **path)
{
	if (redir_actions(cmd))
	{
		perror("");
		free_all(path);
		free_env(get_shell()->env);
		free_all(new_env);
		cleanup_iteration();
		exit(2);
	}
	exec_external(cmd, new_env, path);
	free_all(new_env);
	// free_all(path);
	free_env(get_shell()->env);
	cleanup_iteration();
	if (get_shell()->exit_status == 127)
		exit(127);
	else
		exit(0);
}
