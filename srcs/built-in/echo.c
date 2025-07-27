/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:48:17 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/14 16:28:46 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int		i;
	int		n_flag;
	char	*expanded;

	i = 1;
	n_flag = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		expanded = expand_var(args[i]);
		ft_putstr_fd(expanded, 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		free(expanded);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
