/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:48:17 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/09 12:28:05 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **input)
{
	int	n_flag;
	int	i;

	i = 1;
	n_flag = 0;
	if (input[i] && !ft_strcmp(input[i], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (input[i])
	{
		ft_printf("%s", input[i]);
		if (input[i + 1])
			ft_printf(" ");
		i++;
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	return (0);
}
