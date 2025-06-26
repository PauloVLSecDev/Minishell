/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:48:17 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/25 15:45:51 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ambient_var(char *arg, t_env *env, int has_next)
{
    char *var;

	if (arg[0] == '$' && arg[1] == '$' && arg[2] == '\0')
		ft_putnbr_fd(getpid(), 1);
	if (arg[0] == '$')
    {
		if (!arg[1] || arg[1] == ' ')
            ft_putstr_fd("$", 1);
        else
        {
            var = get_env_value(env, arg + 1);
            if (var)
				ft_putstr_fd(var, 1);
        }
    }
    else
        ft_putstr_fd(arg, 1);
    if (has_next)
        ft_putstr_fd(" ", 1);
}

int ft_echo(char **args)
{
    int i = 1;
    int n_flag = 0;

    if (args[1] && !ft_strcmp(args[1], "-n"))
    {
        n_flag = 1;
        i++;
    }
    while (args[i])
    {
        ambient_var(args[i], get_shell()->env, args[i + 1] != NULL);
        i++;
    }
    if (!n_flag)
        ft_putstr_fd("\n", 1);
    return (0);
}
