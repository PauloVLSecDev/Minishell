/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/04 17:07:09 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node_env(char *name, char *content)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env);
    if (!node)
        return (NULL);
    node->name = name; 
    node->content = content; 
    node->next = NULL;
    return (node);
}

t_env	*insertion_node_env(char **env)
{
	t_env	*head;
	char	**content_split;

	content_split = ft_split(env, "=");
	if (!content_split)
		return (NULL);
}
