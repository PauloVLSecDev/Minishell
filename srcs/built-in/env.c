/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:04:16 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/18 20:20:53 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args)
{
	char	**temp;
	t_env	*node_env;
	int		i;

	i = 0;
	if (args[1])
	{
		ft_printf("env: '%s': No such file or directory\n", args[1]);
		return (127);
	}
	temp = recreate_env(get_shell()->env);
	node_env = get_shell()->env;
	while (node_env)
	{
		if (node_env->content)
			ft_printf("%s=%s\n", node_env->name, node_env->content);
		
		node_env = node_env->next;
	}
	free_all(temp);
	return (0);
}
