/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:17:05 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/10 15:39:03 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*together_all;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	together_all = ft_strjoin(tmp, s3);
	if (!together_all)
	{
		free(tmp);
		return (NULL);
	}
	return (together_all);
}
