/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:14:59 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/10 19:17:57 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap_str(char **i, char **j)
{
	char *temp;
	temp = *i;
	*i = *j;
	*j = temp;
}

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

static int	is_valid_identifier(char *name)
{
	int idx = 0;
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	idx = 1;
	while (name[idx])
	{
		if (!ft_isalnum(name[idx]) && name[idx] != '_')
			return (0);
		idx++;
	}
	return (1);
}

static void	ft_error_export(char *name)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static t_env	*find_env_node(char *name)
{
	t_env *curr = get_shell()->env;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static void	update_node(t_env *node, char *value)
{
	if (value)
	{
		free(node->content);
		node->content = ft_strdup(value);
	}
	
	node->exported = 1;
}

static void	add_env_node(char *name, char *value)
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

// static int	is_equal_or_not(char **args, char *name, char *value, int *i)
// {

// 	if (equal)
// 	{
// 		name = ft_substr(args[*i], 0, equal - args[*i]);
// 		value = ft_strdup(equal + 1);
// 	}
// 	else
// 	{
// 		name = ft_strdup(args[*i]);
// 		value = ft_strdup("\"\"");
// 	}
// 	return (*i);
// }

static int error_identifier(char *name, char *value)
{
	if (!is_valid_identifier(name))
	{
		ft_error_export(name);
		free(name);
		free(value);
		return (1);
	}
	free(name);
	free(value);
	return (0);
}

void	valid_export(char **args, char *name, char *value, int *i)
{
	t_env	*found;
	char	*equal;

	equal = ft_strchr(args[*i], '=');
	if (equal)
	{
		name = ft_substr(args[*i], 0, equal - args[*i]);
		value = ft_strdup(equal + 1);
	}
	else
	{
		name = ft_strdup(args[*i]);
		value = ft_strdup("\"\"");
	}
	if (!error_identifier(name, value))
		return ;
	else
	{
		found = find_env_node(name);
		if (found)
		update_node(found, value);
		else
		add_env_node(name, value);
	}
	free(value);
	free(name);
	
}
