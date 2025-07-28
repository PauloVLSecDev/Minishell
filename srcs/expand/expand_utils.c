/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:49:11 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/28 19:41:58 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*which_expand(char c)
{
	if (c == '?')
		return (ft_itoa(get_shell()->exit_status));
	return (ft_strdup(""));
}

char	*append_str(char *dest, const char *src)
{
	char	*temp;

	temp = ft_strjoin(dest, src);
	if (!temp)
		return (NULL);
	free(dest);
	return (temp);
}

char	*expand_env(char *arg, int *i, t_env *env)
{
	char	*name;
	char	*value;
	int		start;
	int		len;

	start = *i + 1;
	len = 0;
	while (ft_isalnum(arg[start + len]) || arg[start + len] == '_')
		len++;
	name = ft_substr(arg, start, len);
	value = get_env_value(env, name);
	free(name);
	*i = start + len;
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
