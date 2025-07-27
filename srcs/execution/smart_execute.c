/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:05:05 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/26 19:25:56 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	single_child_process(t_cmd *cmd, char **new_env, char **path);
static int	cmd_args_is_null(t_cmd *cmd);

void	smart_execute(t_cmd *cmd)
{
	char	**new_env;
	char	**path;

	path = NULL;
	new_env = NULL;
	if (get_shell()->heredoc_counter == -1)
		set_std_cmd();
	if (cmd_args_is_null(cmd))
		return ;
	if (cmd->next == NULL && get_shell()->must_execute != 1)
	{
		if (is_builtin(cmd->args) != -1)
			exec_builtin(is_builtin(cmd->args), cmd, get_shell()->env);
		else
			exec_single_command(cmd, new_env, path);
	}
	else if (cmd->next != NULL)
		execute_pipeline(cmd);
	else
	{
		get_shell()->must_execute = 0;
		return ;
	}
}

void	exec_single_command(t_cmd *cmd, char **new_env, char **path)
{
	pid_t	pid;
	int		status;

	expand_all_args(cmd);
	path = find_path(get_shell()->env);
	if (!path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return ;
	}
	new_env = recreate_env(get_shell()->env);
	pid = fork();
	if (pid == 0)
		single_child_process(cmd, new_env, path);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			get_shell()->exit_status = 128 + WTERMSIG(status);
		else
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
	free_all(path);
	free_env(get_shell()->env);
	cleanup_iteration();
	if (get_shell()->exit_status == 127)
		exit(127);
	else
		exit(0);
}

static int	cmd_args_is_null(t_cmd *cmd)
{
	if (!cmd->args[0] || !cmd)
	{
		cleanup_iteration();
		return (1);
	}
	return (0);
}
