/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:48:17 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/08 16:21:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	epur_str(char **input)
// {
// 	int		i;
// 	char	*s;

// 	s = input[1];
// 	i = 0;
// 	while (s[i] == ' ' || s[i] == '\t')
// 		i++;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == ' ' || s[i] == '\t')
// 		{
// 			if (s[i + 1] != ' ' && s[i + 1] != '\t' && s[i + 1] != '\0')
// 				write (1, " ", 1);
// 		}
// 		else if (s[i] != ' ' && s[i] != '\t')
// 			write (1, &s[i], 1);
// 		i++;
// 	}
// 	write (1, "\n", 1);
// }

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
