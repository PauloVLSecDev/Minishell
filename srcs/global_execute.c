/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/26 15:56:10 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_all(void)
{
        char **new_env;
        char **path;

        new_env = NULL;
        path = NULL;
        if (!get_shell()->cmd)
            return ; 
        if (is_builtin() != -1)
            exec_builtin(is_builtin());
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
    char *abs_path;
    int status;
    pid_t pid;

    if (!cmd || !cmd->args || !cmd->args[0])
        return ;
    abs_path = join_path_with_cmd(path, cmd);
    if (!abs_path)
	{
		printf("comand not found\n");
        return ;
	}
    pid = fork();
    if (pid == 0)
    {
		execve(abs_path, cmd->args, env);
    	exit(127);
    }
    free(abs_path);
    if (pid > 0)
        waitpid(pid, &status, 0);
}
