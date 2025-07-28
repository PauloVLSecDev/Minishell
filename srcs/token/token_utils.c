/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:54:27 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/27 21:43:08 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_avoid_tokens(char *input, int *i)
// {
// 	while (input[*i] && ft_strchr(AVOID_TOKENS, input[*i]))
// 		(*i)++;
// 	if (input[*i] == '\0')
// 		return (1);
// 	return (0);
// }

int	ft_avoid_tokens(char *input, int *i)
{
    while (input[*i] && ft_strchr(AVOID_TOKENS, input[*i]))
        (*i)++;
    if (input[*i] == '\0')
        return (1);
    if ((input[*i] == DOUBLE_QUOTE && input[*i + 1] == DOUBLE_QUOTE) || (input[*i] == QUOTE && input[*i + 1] == QUOTE))
    {
        *i += 2;
        return (1);
    }
    return (0);
}

static void	extract_redir_value(char *input, int *i, t_token **token,
		t_token **current)
{
	int		start;
	char	*value;

	start = *i;
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
			&& input[*i + 1] == '>'))
		*i += 2;
	else
		(*i)++;
	value = ft_substr(input, start, *i - start);
	append_token(token, current, value);
	free(value);
}

static void	extract_redir_target(char *input, int *i, t_token **token,
		t_token **current)
{
	int		start;
	char	*value;

	if (input[*i] && !is_space(input[*i]) && !ft_strchr(AVOID_TOKENS, input[*i])
		&& !ft_strchr(SPECIALS_CHARS, input[*i]))
	{
		start = *i;
		while (input[*i] && !is_space(input[*i]) && !ft_strchr(AVOID_TOKENS,
				input[*i]) && !ft_strchr(SPECIALS_CHARS, input[*i]))
			(*i)++;
		value = ft_substr(input, start, *i - start);
		append_token(token, current, value);
		free(value);
	}
}

int	extract_redir_or_pipe(char *input, int *i, t_token **token,
		t_token **current)
{
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		extract_redir_value(input, i, token, current);
		extract_redir_target(input, i, token, current);
		return (1);
	}
	return (0);
}
