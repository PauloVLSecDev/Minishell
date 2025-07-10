/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:14:59 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/10 20:08:49 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	sort_env_array(char **array, size_t count)
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
	t_env *node = get_shell()->env;
	char **args;
	size_t count = 0;
	size_t i;

	args = recreate_env(node);
	while (args[count])
		count++;
	sort_env_array(args, count);
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
	t_env *new = malloc(sizeof(t_env));
	t_env *last = get_shell()->env;
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
	t_env	*name_export;
	char	*name = NULL;
	char	*value = NULL;
	int		i;

	i = 1;
	name_export = get_shell()->env;
	if (!args[1])
	{
		print_export();
		return (0);
	}
	while (args[i])
	{
		name = NULL;
		value = NULL;
		valid_export(args, name, value, &i);
		i++;
	}
	return (0);
}

