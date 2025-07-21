/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:00:06 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/21 20:21:14 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_dollar_sign(char *arg, char **expanded)
{
	t_env	*env;
	int		i;
	char	*temp;

	env = get_shell()->env;
	i = 0;
	if (arg[i] == '$')
	{
		if (arg[i + 1] == ' ' || arg[i + 1] == '\0')
			ft_putstr_fd("$", 1);
		if (arg[i + 1] == '$' || arg[i + 1] == '?')
		{
			if (arg[i + 1] == '$')
				ft_putstr_fd("$$", 1);
			temp = which_expand(arg[i + 1]);
			i += 2;
		}
		else
			temp = expand_env(arg, &i, env);
		*expanded = append_str(*expanded, temp);
		free(temp);
	}
	return (i);
}

char	*expand_var(char *arg)
{
	char	*expanded;
	int		i;
	char	buffer[2];
	int		curr_i;

	expanded = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		curr_i = verify_dollar_sign(&arg[i], &expanded);
		if (curr_i > 0)
			i += curr_i;
		else
		{
			buffer[0] = arg[i];
			buffer[1] = '\0';
			expanded = append_str(expanded, buffer);
			i++;
		}
	}
	return (expanded);
}

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
