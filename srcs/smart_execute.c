/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:26:54 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/03 17:02:17 by brunogue         ###   ########.fr       */
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
	pid_t	pid;
	char	**path;
	char	**new_env;
	int		status;

	path = find_path(get_shell()->env);
	if (!path)
		exit (get_shell()->exit_status = 1);
	new_env = recreate_env(get_shell()->env);
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

// void	exec_single_command(t_cmd *cmd)
// {
// 	pid_t	pid;
// 	char	**path;
// 	char	**new_env;
// 	int		status;
// 	int		exec_exit;

// 	path = find_path(get_shell()->env);
// 	if (!path)
// 		exit (get_shell()->exit_status = 1);
// 	new_env = recreate_env(get_shell()->env);
// 	pid = fork();
// 	exec_exit = exec_external(cmd, new_env, path);
// 	if (pid == 0)
// 	{
// 		if (exec_exit != 0)
// 		{
// 			ft_putstr_fd("command not found\n", 2);
// 			free_env(get_shell()->env);
// 			cleanup_iteration();
// 			exit(exec_exit);
// 		}
// 		free_all(new_env);
// 		free_all(path);
// 		exit(0);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		get_shell()->exit_status = WEXITSTATUS(status);
// 		free_all(path);
// 		free_all(new_env);
// 	}
// }
