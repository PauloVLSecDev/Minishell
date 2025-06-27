/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/27 17:41:56 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_all(t_cmd *cmd)
{
        char **new_env;
        char **path;
		int builtin_index;

        new_env = NULL;
        path = NULL;
        if (!cmd)
            return ; 
		builtin_index = is_builtin(cmd->args);
		if (builtin_index != -1)
		{
            exec_builtin(builtin_index, cmd);
			exit(0);
		}
        else 
        {
            new_env = recreate_env(get_shell()->env);
            path = find_path(get_shell()->env);
            exec_external(cmd, new_env, path);
        }
		free_all(new_env);
		free_all(path);
}

void exec_external(t_cmd *cmd, char **env, char **path)
{
	char *abs_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	abs_path = join_path_with_cmd(path, cmd);
	if (!abs_path)
	{
		printf("comand not found\n");
        return ;
	}
	execve(abs_path, cmd->args, env);
    free(abs_path);
}
