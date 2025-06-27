/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/27 19:02:02 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all(void)
{
    char	**new_env;
    char	**path;
	int		builtin_code;

	builtin_code = is_builtin();
    new_env = NULL;
    path = NULL;
    if (!get_shell()->cmd)
        return ;
    expand_all_args(get_shell()->cmd, get_shell()->env);
    if (builtin_code != -1)
        exec_builtin(builtin_code);
    else
    {
        new_env = recreate_env(get_shell()->env);
        path = find_path(get_shell()->env);
        exec_external(get_shell()->cmd, new_env, path);
    }
    free_all(new_env);
    free_all(path);
}

void exec_external(t_cmd *cmd, char **env, char **path)
{
	char	*abs_path;
	int		status;
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;

	abs_path = join_path_with_cmd(path, cmd);
	if (!abs_path)
	{
		ft_putstr_fd("command not found\n", 2);
		get_shell()->exit_status = 127;
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(abs_path, cmd->args, env);
		exit(127);
	}
	else if (pid < 0)
	{
		ft_putstr_fd("fork failed\n", 2);
		get_shell()->exit_status = 1;
		free(abs_path);
		return ;
	}
	free(abs_path);
	waitpid(pid, &status, 0);
	get_shell()->exit_status = WEXITSTATUS(status);
}


void	expand_all_args(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*expanded;
	
	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_var(cmd->args[i], env);
        free(cmd->args[i]);
        cmd->args[i] = expanded;
        i++;        
	}
}