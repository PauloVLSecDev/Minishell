/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/12 19:33:38 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_all(t_env *env, t_cmd *cmd)
{
        char **new_env;
        char **path;

        new_env = NULL;
        path = NULL;
        if (!cmd)
            return ; 
        if (is_builtin(cmd->args[0]) != -1)
            exec_builtin(cmd, env, is_builtin(cmd->args[0]));
        else 
        {
            new_env = recreate_env(env);
            path = find_path(env);
            exec_external(cmd, new_env, path);
        }
		free_all(new_env);
		free_all(path);
}

void    exec_external(t_cmd *cmd, char **env, char **path)
{
    char *abs_path;
    int status;
    int pid;

	status = 0;
	if (cmd == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
	    abs_path = join_path_with_cmd(path, cmd);
		if (execve(abs_path, cmd->args, env) == -1)
		{
			perror("error in execute comand");
            free(abs_path);
		    exit(1);
		}
        free(abs_path);
	}
	if (pid > 0)
		waitpid(pid, &status, 0);
}
