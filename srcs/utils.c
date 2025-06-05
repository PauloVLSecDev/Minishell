/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:03:07 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/05 20:44:01 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*insertion_node_end_in_env(char **env)
{
	t_env	*head;
	t_env	*current_node;
	t_env	*node_to_add;
	char	**content_split;
    int i;

    i = 0;
	content_split = ft_split(env[0], '=');
	if (!content_split)
        return (NULL);
    head = create_node_env(content_split[0], content_split[1]);
    if (!head)
    {
        free_all(content_split);
        return (NULL);
    }
    free_all(content_split);
    current_node = head;
    i++;
    while (env[i] != NULL)
    {
	    content_split = ft_split(env[i], '=');
    	if (!content_split)
            return (NULL);
        node_to_add = create_node_env(content_split[0], content_split[1]);
        if (!node_to_add)
        {
            free_env(current_node);
            return (NULL);
        }
        current_node->next = node_to_add; 
        current_node = current_node->next;
        free_all(content_split);
        i++;
    }
    t_env *curr = head;
    i = 0;
    while (curr != NULL)
    {
        printf("conten in nome number %i %s %s\n ", i, curr->name, curr->content);
        curr = curr->next;
        i++;
    }
    return (head);
}

void    free_env(t_env *env)
{
        t_env *temp;
        t_env *next;

        temp = env;
        while (temp != NULL)
        {
            next = temp->next;
            free(temp->name); 
            free(temp->content); 
            free(temp); 
            temp = next;
        }
}
