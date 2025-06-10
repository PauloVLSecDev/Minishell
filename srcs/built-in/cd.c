/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:45:10 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/10 14:46:20 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_cd(char **args, t_env *env)
{
	int		i;
	char	cwd[PATH_MAX];
	char	*home_path;

	home_path = get_env_value(env, "HOME");
	if (!home_path)
		write (2, "cd: HOME not set\n", 17);
	i = 1;
	if (!args[i] || args[i][0] == '\0')
	{
		chdir(home_path);
		getcwd(cwd, PATH_MAX);
		return (0);
	}
	if (args[1] && args[2])
	{
		ft_putendl_fd("cd: Too many arguments.\n", 2);
		return (1);
	}
	if (args[1])
	{
		if (!args[1])
		{
			write(2, "cd: directory not found.\n", 27);
		}
		chdir(args[1]);
		getcwd(cwd, PATH_MAX);
	}
	return (1);
}
