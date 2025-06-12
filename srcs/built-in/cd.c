/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:45:10 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/12 19:00:08 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **args, t_shell *sh)
{
    char *home ;
	
	home = get_env_value(sh->env, "HOME");
    if (!args[1] || args[1][0] == '\0')
    {
        if (!home)
        {
            ft_putendl_fd("cd: HOME not set.", 2);
            return (1);
        }
        if (chdir(home) != 0)
        {
            perror("cd");
            return (1);
        }
    }
    else if (args[2])
    {
        ft_putendl_fd("cd: Too many arguments.", 2);
        return (1);
    }
    else if (chdir(args[1]) != 0)
    {
        perror("cd");
        return (1);
    }
    return (0);
}
