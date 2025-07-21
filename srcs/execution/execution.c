/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:23:24 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/21 20:46:52 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*access_valid(t_cmd *cmd, char **path);

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
	t_env	*curr_env;
	char	*absolute_env_line;
	int		i;

	i = 0;
	absolute_env_line = NULL;
	curr_env = env;
	env_array = malloc((count_nodes(env) + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	while (curr_env != NULL)
	{
		if (curr_env->content)
			env_array[i] = ft_join_three(curr_env->name, "=",
					curr_env->content);
		else
			env_array[i] = ft_strdup(curr_env->name);
		curr_env = curr_env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	*join_path_with_cmd(char **path, t_cmd *cmd)
{
	char	*path_with_cmd;
	int		i;

	i = 0;
	path_with_cmd = NULL;
	if (!path)
		return (NULL);
	if (ft_strchr(cmd->args[0], '/'))
		return (access_valid(cmd, path));
	while (path[i] != NULL)
	{
		path_with_cmd = ft_join_three(path[i], "/", cmd->args[0]);
		if (access(path_with_cmd, X_OK) == 0)
		{
			free_all(path);
			return (path_with_cmd);
		}
		free(path_with_cmd);
		i++;
	}
	free_all(path);
	return (NULL);
}

static char	*access_valid(t_cmd *cmd, char **path)
{
	if (access(cmd->args[0], X_OK) == 0)
	{
		free_all(path);
		return (ft_strdup(cmd->args[0]));
	}
	if (path)
		free_all(path);
	return (NULL);
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
	while (current_node && current_node->name && ft_strcmp(current_node->name,
			"PATH"))
		current_node = current_node->next;
	if (current_node == NULL)
		return (NULL);
	if (*current_node->name == '\0' || *current_node->content == '\0')
		return (NULL);
	path = ft_split(current_node->content, ':');
	if ((!path) || (!*path))
		return (NULL);
	return (path);
}
