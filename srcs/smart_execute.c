/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:26:54 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/03 17:17:57 by brunogue         ###   ########.fr       */
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

	path = find_path(get_shell()->env);
	new_env = recreate_env(get_shell()->env);
	if (!path)
		exit (get_shell()->exit_status = 1);
	pid = fork();
	if (pid == 0)
	{
		exec_external(cmd, new_env, path);
		free_all(new_env);
		free_all(path);
		if (get_shell()->exit_status == 127)
			exit(127);
		else
			exit (0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		get_shell()->exit_status = WEXITSTATUS(status);
	}
	free_all(path);
	free_all(new_env);
}
