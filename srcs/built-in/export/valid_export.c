/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:57:47 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/11 19:59:45 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_export(char **args, int *i)
{
	char	*arg;
	char	*equal;
	char	*name;
	char	*value;

	arg = args[*i];
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		name = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
	}
	else
	{
		name = ft_strdup(arg);
		value = ft_strdup("\"\"");
	}
	if (error_identifier(name, value))
		return ;
	correct_identifier(name, value);
	free(name);
	free(value);
}

int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	error_identifier(char *name, char *value)
{
	if (!is_valid_identifier(name))
	{
		ft_error_export(name);
		free(name);
		free(value);
		return (1);
	}
	return (0);
}

void	correct_identifier(char *name, char *value)
{
	t_env	*found;

	found = find_env_node(name);
	if (found)
		update_node(found, value);
	else
		add_env_node(name, value);
}
