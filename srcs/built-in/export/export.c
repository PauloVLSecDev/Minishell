/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:14:59 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/11 19:59:32 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_sort_env_array(char **array, size_t count)
{
	size_t i;
	size_t j;
	
	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			ft_swap_str(&array[i], &array[j]);
			j++;
		}
		i++;
	}
}

void	print_export(void)
{
	t_env *node;
	char **args;
	size_t count;
	size_t i;
	
	node = get_shell()->env;
	args = recreate_env(node);
	count = 0;
	while (args[count])
	count++;
	_sort_env_array(args, count);
	i = 0;
	while (i < count)
	{
		printf("declare -x %s\n", args[i]);
		i++;
	}
	free_all(args);
}

void	update_node(t_env *node, char *value)
{
	if (value)
	{
		free(node->content);
		node->content = ft_strdup(value);
	}
	node->exported = 1;
}

void	add_env_node(char *name, char *value)
{
	t_env *new;
	t_env *last;

	last = get_shell()->env;
	new = malloc(sizeof(t_env));
	if (!new)
		return;
	new->name = ft_strdup(name);
	new->content = value ? ft_strdup(value) : NULL;
	new->exported = 1;
	new->next = NULL;
	if (!last)
	{
		get_shell()->env = new;
		return;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

int	ft_export(char **args)
{
	int i;

	i = 1;
	if (!args[1])
	{
		print_export();
		return (0);
	}
	while (args[i])
	{
		valid_export(args, &i);
		i++;
	}
	return (0);
}
