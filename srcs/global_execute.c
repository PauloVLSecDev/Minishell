/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/17 16:16:58 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_all(t_shell *sh)
{
        char **new_env;
        char **path;

        new_env = NULL;
        path = NULL;
        if (!sh->cmd)
            return ; 
        if (is_builtin(sh) != -1)
            exec_builtin(sh, is_builtin(sh));
        else 
        {
            new_env = recreate_env(sh->env);
            path = find_path(sh->env);
            exec_external(sh->cmd, new_env, path);
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
        return ;
    pid = fork();
    if (pid == 0)
    {
        execve(abs_path, cmd->args, env);
        perror("execve");
        exit(127);
    }
    free(abs_path);
    if (pid > 0)
        waitpid(pid, &status, 0);
}
