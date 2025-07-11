/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:59:39 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/11 19:59:22 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_swap_str(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_error_export(char *name)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

t_env	*find_env_node(char *name)
{
	t_env *curr;

	curr = get_shell()->env;
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
