/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:23:24 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/10 14:46:47 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nodes(t_env *env)
{
	t_env	*new;
	int		len;

	len = 0;
	new = env;
	if (!env)
		return (0);
	while (new != NULL)
	{
		new = new->next;
		len++;
	}
	return (len);
}

char	**recreate_env(t_env *env)
{
	char	**env_array;
	char	*join_name;
	char	*join_equal;
	t_env	*current_env;
	char	*absolute_env_line;
	int		i;

	absolute_env_line = NULL;
	current_env = env;
	i = 0;
	env_array = malloc((count_nodes(env) + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	while (current_env != NULL)
	{
		join_name = current_env->name;
		join_equal = ft_strjoin(join_name, "=");
		absolute_env_line = ft_strjoin(join_equal, current_env->content);
		env_array[i] = ft_strdup(absolute_env_line);
		free(join_equal);
		free(join_name);
		free(absolute_env_line);
		current_env = current_env->next;
		i++;
	}
	return (env_array);
}
void	execution_cmd(t_env *env, t_cmd *cmd)
{
	char	*abs_path;
	char	**new_envp;

	if (exec_builtin(cmd) != -1)
		return ;
	new_envp = recreate_env(env);
	abs_path = join_path_with_cmd(find_path(env), cmd);
	execve(abs_path, cmd->args, new_envp);
}

char	*join_path_with_cmd(char **path, t_cmd *cmd)
{
	char	*join_slash;
	char	*path_with_cmd;
	int		i;

	i = 0;
	join_slash = NULL;
	path_with_cmd = NULL;
	if (!path)
		return (NULL);
	while (path[i] != NULL)
	{
		join_slash = ft_strjoin(path[i], "/");
		path_with_cmd = ft_strjoin(join_slash, cmd->args[0]);
		if (access(path_with_cmd, X_OK) == 0)
		{
			free(join_slash);
			free(path_with_cmd);
			return (path_with_cmd);
		}
		free(join_slash);
		free(path_with_cmd);
		i++;
	}
	return (path_with_cmd);
}

char	**find_path(t_env *env)
{
	t_env	*current_node;
	char	**path;

	if (!env)
		return (NULL);
	current_node = env;
	if (!current_node)
		return (NULL);
	while (current_node->name && ft_strcmp(current_node->name, "PATH"))
		current_node = current_node->next;
	path = ft_split(current_node->content, ':');
	if (!path)
		return (NULL);
	return (path);
}
