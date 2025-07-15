/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:45:10 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/15 19:33:13 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*home;

	home = get_env_value(get_shell()->env, "HOME");
	if (!args[1] || args[1][0] == '\0')
	{
		if (verify_home(home))
			return (1);
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

int	verify_home(char *home)
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
	return (0);
}
