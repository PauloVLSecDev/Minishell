/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/03 16:58:11 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_all(t_cmd *cmd)
{
        char	**new_env;
        char	**path;
		int		isbuiltin;

        new_env = NULL;
        path = NULL;
        if (!cmd)
            return ;
    	expand_all_args(cmd, get_shell()->env);
		isbuiltin = is_builtin(cmd->args);
		if (isbuiltin != -1)
		{
            get_shell()->exit_status = exec_builtin(isbuiltin, cmd);
			return ;
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

int exec_external(t_cmd *cmd, char **env, char **path)
{
	char	*abs_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (127);
	abs_path = join_path_with_cmd(path, cmd);
	if (!abs_path)
	{
		ft_putstr_fd("command not found\n", 2);
		get_shell()->exit_status = 127;
		free_env(get_shell()->env);
		cleanup_iteration();
		printf("entrou, error commando exec tesfaf\t\n");
		return (127);
	}
	if (execve(abs_path, cmd->args, env) == -1)
	{
		free_env(get_shell()->env);
		cleanup_iteration();
		exit(get_shell()->exit_status = 127);	
	}
    free(abs_path);
	return (0);
}

// int	exec_external(t_cmd *cmd, char **env, char **path)
// {
// 	char	*abs_path;

// 	if (!cmd || !cmd->args || !cmd->args[0])
// 		return (127);
// 	abs_path = join_path_with_cmd(path, cmd);
// 	if (!abs_path)
// 	{
// 		ft_putstr_fd("command not found\n", 2);
// 		get_shell()->exit_status = 127;
// 		free_env(get_shell()->env);
// 		cleanup_iteration();
// 		exit(127);
// 		return (127);
// 	}
// 	if (execve(abs_path, cmd->args, env) == -1)
// 	{
// 		free(abs_path);
// 		free_env(get_shell()->env);
// 		cleanup_iteration();
// 		exit(get_shell()->exit_status = 127);
// 		return (127);	
// 	}
//     free(abs_path);
// 	return (0);
// }

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
