/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:45:10 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/10 16:13:31 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, t_env *env)
{
	char	cwd[PATH_MAX];
	char	*home_path;

	home_path = get_env_value(env, "HOME");
	if (!args[1] || args[1][0] == '\0')
	{
		if (!home_path)
		{
			ft_putendl_fd("cd: HOME not set.", 2);
			return (1);
		}
		if (chdir(home_path) != 0)
		{
			perror("cd");
			return (1);
		}
		getcwd(cwd, PATH_MAX);
		return (0);
	}
	if (args[1] && args[2])
	{
		ft_putendl_fd("cd: Too many arguments.\n", 2);
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	getcwd(cwd, PATH_MAX);
	return (1);
}
