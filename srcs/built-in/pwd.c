/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:29:00 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/11 12:46:22 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	else
		perror("pwd");
}