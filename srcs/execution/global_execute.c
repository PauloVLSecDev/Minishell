/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/26 20:21:24 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_builtin(int isbuiltin, t_cmd *cmd, t_env *envp);

void	exec_all(t_cmd *cmd, t_env *envp)
{
	char	**new_env;
	char	**path;
	int		isbuiltin;

	new_env = NULL;
	path = NULL;
	if (!cmd)
		return ;
	expand_all_args(cmd);
	isbuiltin = is_builtin(cmd->args);
	if (valid_builtin(isbuiltin, cmd, envp))
		return ;
	new_env = recreate_env(envp);
	path = find_path(envp);
	exec_external(cmd, new_env, path);
	free_all(new_env);
	free_all(path);
}

void	exec_external(t_cmd *cmd, char **env, char **path)
{
	char	*abs_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	abs_path = join_path_with_cmd(path, cmd);
	if (!abs_path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(" command not found\n", 2);
		get_shell()->exit_status = 127;
		cleanup_iteration();
		return ;
	}
	if (execve(abs_path, cmd->args, env) == -1)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(" command not found\n", 2);
		free(abs_path);
		cleanup_iteration();
		exit(get_shell()->exit_status = 127);
	}
	free(abs_path);
}

static int	valid_builtin(int isbuiltin, t_cmd *cmd, t_env *envp)
{
	int	exit_code;

	exit_code = 0;
	if (isbuiltin != -1)
	{
		exit_code = exec_builtin(isbuiltin, cmd, envp);
		get_shell()->exit_status = exit_code;
		cleanup_iteration();
		return (1);
	}
	return (0);
}

void	expand_all_args(t_cmd *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_var(cmd->args[i]);
		free(cmd->args[i]);
		cmd->args[i] = expanded;
		i++;
	}
}
