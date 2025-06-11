/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:42:15 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/11 19:41:15 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;
	
	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	count_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_exit(char **args)
{
	int		ac;
	long	code;
	
	ac = count_arg(args);
	if (ac > 2)
	{
		ft_putstr_fd("exit: Too many arguments", 2);
		return (1);
	}
	if (args[1] && !is_numeric(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd("exit: numeric argument required", 2);
		exit(2);
	}
	if (args[1])
	{
		code = ft_atoi(args[1]);
		exit((unsigned char)code);
	}
	exit(0);
}
