/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:00:06 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/27 21:02:41 by pvitor-l         ###   ########.fr       */
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

int	ternary(int condition, int true_val, int false_val)
{
	if (condition)
		return (true_val);
	return (false_val);
}

// char *expand_var(char *arg)
// {
//     char      *expanded;
//     t_qmode    in_quotes;
//     int        i;
//     int        consumed;
//     char       buffer[2];

//     i = 0;
//     in_quotes = QUOTE_NONE;
//     expanded  = ft_strdup("");
//     if (!expanded)
//         return (NULL);

//     while (arg[i])
//     {
//         if (arg[i] == QUOTE && in_quotes != QUOTE_DOUBLE)
//         {
//             in_quotes = ternary(in_quotes == QUOTE_SINGLE, QUOTE_NONE,
//	QUOTE_SINGLE);
//             i++;
//         }
//         else if (arg[i] == DOUBLE_QUOTE && in_quotes != QUOTE_SINGLE)
//         {
//             in_quotes = ternary(in_quotes == QUOTE_DOUBLE, QUOTE_NONE,
//		QUOTE_DOUBLE);
//             i++;
//         }
//         else if (arg[i] == '$' && in_quotes != QUOTE_SINGLE)
//         {
//             consumed = verify_dollar_sign(&arg[i], &expanded);
//             if (consumed > 0)
//                 i += consumed;
//             else
//             {
//                 buffer[0] = arg[i++];
//                 buffer[1] = '\0';
//                 expanded = append_str(expanded, buffer);
//             }
//         }
//         else
//         {
//             buffer[0] = arg[i++];
//             buffer[1] = '\0';
//             expanded = append_str(expanded, buffer);
//         }
//     }
//     return (expanded);
// }

static t_qmode	toggle_quote(char c, t_qmode in_quotes)
{
	if (c == QUOTE && in_quotes != QUOTE_DOUBLE)
		return (ternary(in_quotes == QUOTE_SINGLE, QUOTE_NONE, QUOTE_SINGLE));
	if (c == DOUBLE_QUOTE && in_quotes != QUOTE_SINGLE)
		return (ternary(in_quotes == QUOTE_DOUBLE, QUOTE_NONE, QUOTE_DOUBLE));
	return (in_quotes);
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

char	*expand_var(char *arg, char *expanded)
{
	t_qmode	in_quotes;
	int		i;
	t_qmode	new_q;

	i = 0;
	in_quotes = QUOTE_NONE;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (arg[i])
	{
		new_q = toggle_quote(arg[i], in_quotes);
		if (new_q != in_quotes)
		{
			in_quotes = new_q;
			i++;
			continue ;
		}
		if (arg[i] == '$' && in_quotes != QUOTE_SINGLE)
		{
			if (try_handle_dollar(arg, &i, &expanded))
				continue ;
		}
		expanded = append_literal(expanded, arg, &i);
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
