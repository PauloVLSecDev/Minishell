/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:00:06 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/28 19:42:38 by brunogue         ###   ########.fr       */
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

static int	try_handle_dollar(char *arg, int *i, char **expanded)
{
	int	consumed;

	consumed = verify_dollar_sign(&arg[*i], expanded);
	if (consumed > 0)
	{
		*i += consumed;
		return (1);
	}
	return (0);
}

static char	*append_literal(char *expanded, const char *arg, int *i)
{
	char	buf[2];

	buf[0] = arg[*i];
	buf[1] = '\0';
	(*i)++;
	return (append_str(expanded, buf));
}

static int	handle_quote_change(char c, t_qmode *in_quotes, int *i)
{
	t_qmode	new_q;

	new_q = toggle_quote(c, *in_quotes);
	if (new_q != *in_quotes)
	{
		*in_quotes = new_q;
		(*i)++;
		return (1);
	}
	return (0);
}

char	*expand_var(char *arg, char *expanded)
{
	t_qmode	in_quotes;
	int		i;

	i = 0;
	in_quotes = QUOTE_NONE;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (arg[i])
	{
		if (handle_quote_change(arg[i], &in_quotes, &i))
			continue ;
		if (arg[i] == '$' && in_quotes != QUOTE_SINGLE)
		{
			if (try_handle_dollar(arg, &i, &expanded))
				continue ;
		}
		expanded = append_literal(expanded, arg, &i);
	}
	return (expanded);
}
