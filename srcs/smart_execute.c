/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:26:54 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/01 21:32:29 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	smart_execute(t_cmd *cmd)
{
	if (cmd->next == NULL)
	{
		if (is_builtin(cmd->args) != -1)
			exec_builtin(is_builtin(cmd->args), cmd);
		else 
			exec_single_command(cmd);
	}
	else if (cmd->next != NULL)
		execute_pipeline(cmd);
	else 
		return ;
}

void	exec_single_command(t_cmd *cmd)
{
	pid_t pid;
	char **path;
	char **new_env;
	int	status;

	path = find_path(get_shell()->env);
	if (!path)
		exit (get_shell()->exit_status = 1);
	new_env = recreate_env(get_shell()->env);
	pid = fork();
	if (pid == 0)
	{
		exec_external(cmd, new_env, path);\
		free_all(new_env);
		free_all(path);
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
