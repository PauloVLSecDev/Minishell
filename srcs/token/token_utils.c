/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:54:27 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/21 20:21:22 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_avoid_tokens(char *input, int *i)
{
	while (input[*i] && ft_strchr(AVOID_TOKENS, input[*i]))
		(*i)++;
	if (input[*i] == '\0')
		return (1);
	return (0);
}

int	extract_redir_or_pipe(char *input, int *i, t_token **token,
		t_token **current)
{
	int		start;
	char	*value;

	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		start = *i;
		if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
				&& input[*i + 1] == '>'))
			*i += 2;
		else
			(*i)++;
		value = ft_substr(input, start, *i - start);
		append_token(token, current, value);
		free(value);
		return (1);
	}
	return (0);
}
