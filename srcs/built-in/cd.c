/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:45:10 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/10 14:19:49 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_arg(char **args)
{
	
}

int	ft_cd(char **args, t_env *env)
{
	int		i;
	char	cwd[PATH_MAX];
	char	*home_path = NULL;

	home_path = get_env_value(env, "HOME");
	ft_printf("%s", home_path);
	if (!home_path)
		write (2, "cd: HOME not set\n", 17);
	i = 1;
	if (!args[i] || args[i][0] == '\0')
	{
		chdir(home_path);
		getcwd(cwd, PATH_MAX);
		return (1);
	}
	cd_arg(args);
	return (-1);
}
