/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/27 15:45:07 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all(t_cmd *cmd)
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
	if (isbuiltin != -1)
	{
		get_shell()->exit_status = exec_builtin(isbuiltin, cmd);
		cleanup_iteration();
		return ;
	}
	else
	{
		new_env = recreate_env(get_shell()->env);
		path = find_path(get_shell()->env);
		exec_external(cmd, new_env, path);
		free_all(new_env);
	}
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

static char *strip_quotes(char *s)
{
    int   len;
    char *out;

    if (!s)
        return NULL;
    len = ft_strlen(s);
    if (len >= 2 && ((s[0] == '\'' && s[len-1] == '\'') ||
                     (s[0] == '"'  && s[len-1] == '"')))
    {
        out = malloc(len - 1);
        if (!out)
            return NULL;
        ft_memmove(out, s + 1, len - 2);
        return out;
    }
    return ft_strdup(s);
}

void expand_all_args(t_cmd *cmd)
{
    int   i;
    char *tmp;
    char *noquotes;

    while (cmd)
    {
        i = 0;
        while (cmd->args && cmd->args[i])
        {
            tmp = expand_var(cmd->args[i]);
            free(cmd->args[i]);
            noquotes = strip_quotes(tmp);
            free(tmp);
            cmd->args[i] = noquotes;
            i++;
        }
        cmd = cmd->next;
    }
}


// void	expand_all_args(t_cmd *cmd)
// {
// 	int		i;
// 	char	*expanded;

// 	i = 0;
// 	while (cmd->args[i])
// 	{
// 		expanded = expand_var(cmd->args[i]);
// 		free(cmd->args[i]);
// 		cmd->args[i] = expanded;
// 		i++;
// 	}
// }
