/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/04 19:03:07 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *env)
{
	char	*env_var_name;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (env == NULL)
		return (NULL);
	while (env[len] && env[len] != '=')
		len++;
	if (env[len] != '=')
		return (NULL);
	env_var_name = malloc((len + 1) * sizeof(char));
	if (!env_var_name)
		return (NULL);
	while (env[i] && env[i] != '=')
	{
		env_var_name[i] = env[i];
		i++;
	}
	env_var_name[i] = '\0';
	return (env_var_name);
}

char	*get_env_value(t_env *env, char *name)
{
	t_env	*temp;

	if (name == NULL)
		return (NULL);
	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*create_node_env(char *name, char *content)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = NULL;
	node->content = NULL;
	if (name)
		node->name = ft_strdup(name);
	if (content)
		node->content = ft_strdup(content);
	node->next = NULL;
	return (node);
}

t_env	*linked_node_env(char **env)
{
	t_env	*head;
	t_env	*current_node;
	char	*env_name;
	int		i;
	char	*content;

	i = 1;
	env_name = get_env_name(env[0]);
	content = ft_strchr(env[0], '=');
	head = create_node_env(env_name, (content += 1));
	if (!head)
		return (NULL);
	free(env_name);
	current_node = head;
	while (env[i] != NULL)
	{
		env_name = get_env_name(env[i]);
		content = ft_strchr(env[i], '=');
		insert_node(env_name, current_node, (content += 1));
		free(env_name);
		current_node = current_node->next;
		i++;
	}
	return (head);
}

void	insert_node(char *env_name, t_env *curr_node, char *content)
{
	t_env	*node_to_add;

	node_to_add = create_node_env(env_name, content);
	if (!node_to_add)
		return ;
	curr_node->next = node_to_add;
}
