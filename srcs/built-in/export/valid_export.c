/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:57:47 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/10 20:09:16 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_export(char **args, char *name, char *value, int *i)
{
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
	correct_identifier(name, value);
	free(value);
	free(name);
}

int	is_valid_identifier(char *name)
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

int error_identifier(char *name, char *value)
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

void	correct_identifier(char *name, char *value)
{
	t_env	*found;

	found = find_env_node(name);
	if (found)
		update_node(found, value);
	else
		add_env_node(name, value);
	free(name);
	free(value);
}
