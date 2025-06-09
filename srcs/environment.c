/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/06 21:30:29 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *env)
{
	char	*environment_variable_name;
	int		i;
	int		len;

	i = 0;
	len = 0; if (env == NULL)
		return (NULL);
	while (env[len] != '=')
		len++;
	environment_variable_name = (char *)malloc(len * sizeof(char));
	if (!environment_variable_name)
		return (NULL);
	while (env[i] && env[i] != '=')
	{
		environment_variable_name[i] = env[i];
		i++;
	}
	return (environment_variable_name);
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
    char    *env_name;
	int		i;
    
	i = 1;
	env_name = get_env_name(env[0]);
	head = create_node_env(env_name, ft_strchr(env[0], '='));
	if (!head)
	{
		free(env_name);
		return (NULL);
	}
	current_node = head;
	while (env[i] != NULL)
	{
		env_name = get_env_name(env[i]);
        insert_node(env[i], env_name, current_node);
        free(env_name);
		current_node = current_node->next;
        i++;
	}
	return (head);
}

void   insert_node(char *env, char *env_name, t_env *current_node)
{
        t_env *node_to_add;

		node_to_add = create_node_env(env_name, ft_strchr(env, '='));
		if (!node_to_add)
		{
			free(env_name);
			return ;
		}
		current_node->next = node_to_add;
}
