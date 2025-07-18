/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:57:47 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/18 18:37:41 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_export(char **args, int *i)
{
	char	*name;
	char	*value;
	char	*equal;
	int		len;

	equal = ft_strchr(args[*i], '=');
	if (equal)
	{
		len = equal - args[*i];
		name = ft_substr(args[*i], 0, len);
		value = ft_strdup(equal + 1);
	}
	else
	{
		name = ft_strdup(args[*i]);
		value = NULL;
	}
	if (error_identifier(name, value))
		return ;
	correct_identifier(name, value);
	free(name);
	free(value);
}


// void valid_export(char **args, int *i)
// {
//     char  *name;
//     char  *value;
//     char  *equal;

//     equal = ft_strchr(args[*i], '=');
//     if (equal)
//     {
//         name  = ft_substr(args[*i], 0, equal - args[*i]);
//         value = ft_strdup(equal + 1);
//         if (!error_identifier(name, value))
//             correct_identifier(name, value);
//         free(value);
//     }
//     else
//     {
//         name = ft_strdup(args[*i]);
//         if (!error_identifier(name, NULL))
//             value = ft_strdup("\'\'");
//     }
//     free(name);
// }



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
