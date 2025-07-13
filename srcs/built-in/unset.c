/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:24:59 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/13 16:43:21 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_env_node(t_env **env, char *name)
{
	t_env *current;
	t_env *prev;
	
	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (!ft_strcmp(current->name, name))
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			free(current->name);
			free(current->content);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_env **env, char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		remove_env_node(env, args[i]);
		i++;
	}
	cleanup_iteration();
	return (0);
}
