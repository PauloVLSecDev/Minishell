/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:00:06 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/25 19:52:49 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(char *arg, t_env *env)
{
	char	*out;
	char	*temp;
	int		i;
	char	buffer[2];
	
	out = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] == '$' || arg[i + 1] == '?')
			{
				temp = which_expand(arg[i + 1]);
				i = i + 2;
			}
			else
				temp = other_function();
			out = append_str(out, temp);
			free(temp);
		}
		else
		{
			buffer[0] = arg[i];
			buffer[1] = '\0';
			out = append_str(out, buffer);
			i++;
		}
	}
	return (out);
}

static char	*which_expand(char c)
{
	if (c == '$')
		return (ft_itoa(getpid()));
	if (c == '?')
		return (ft_itoa(get_shell()->exit_status));
	return (ft_strdup(""));
}

static char	*append_str(char *dest, const char *src)
{
	char	*temp;

	temp = ft_strjoin(dest, src);
	free(dest);
	return (temp);
}
