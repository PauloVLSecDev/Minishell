/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:04:16 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/11 17:32:40 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_env *env)
{
	char	**temp;
	int		i;

	i = 0;
	if (args[1])
	{
		ft_printf("env: '%s': No such file or directory", args[1]);
		return (127);
	}
	temp = recreate_env(env);
	while (temp[i])
	{
		ft_printf("%s\n", temp[i]);
		i++;
	}
	free_all(temp);
	return (0);
	char	*temp;

	args = recreate_env(env);
}
