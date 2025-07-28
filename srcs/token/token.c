/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:28:11 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/28 20:04:27 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	find_token_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (TOKEN_PIPE);
	if (!ft_strcmp(str, "<"))
		return (TOKEN_REDIR_IN);
	if (!ft_strcmp(str, ">"))
		return (TOKEN_REDIR_OUT);
	if (!ft_strcmp(str, "<<"))
		return (TOKEN_HEREDOC);
	if (!ft_strcmp(str, ">>"))
		return (TOKEN_APPEND);
	else
		return (TOKEN_WORD);
}

int	handle_quotes(char *inp, int *i, t_token **tok, t_token **cur)
{
	int		quote_pos;
	char	delim;
	char	*value;
	int		end_pos;
	char	*joined;

	quote_pos = *i;
	delim = inp[*i];
	(*i)++;
	while (inp[*i] && inp[*i] != delim)
		(*i)++;
	end_pos = *i;
	if (inp[*i] == delim)
		(*i)++;
	value = ft_substr(inp, quote_pos, end_pos - quote_pos + 1);
	if (*cur && quote_pos > 0 && !is_space(inp[quote_pos - 1]))
	{
		joined = ft_strjoin((*cur)->value, value);
		free((*cur)->value);
		(*cur)->value = joined;
	}
	else
		append_token(tok, cur, value);
	free(value);
	return (1);
}

static void	token_of_tokenization(char *input, int *i, t_token **token,
		t_token **current)
{
	char	*value;
	int		start;
	char	*joined;

	start = *i;
	while (input[*i] && !ft_strchr(AVOID_TOKENS, input[*i])
		&& !ft_strchr(SPECIALS_CHARS, input[*i]) && !(is_space(input[*i])))
		(*i)++;
	if (*i > start)
	{
		value = ft_substr(input, start, *i - start);
		if (start == 0 || is_space(input[start - 1]) || *current == NULL)
			append_token(token, current, value);
		else
		{
			joined = ft_strjoin((*current)->value, value);
			free((*current)->value);
			(*current)->value = joined;
		}
		free(value);
	}
}

t_token	*tokenization(t_token *token, char *input, t_token *current)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_avoid_tokens(input, &i))
			continue ;
		if (redir_or_pipe(input, &i, &token, &current))
			continue ;
		if (input[i] != TOKEN_HEREDOC && (input[i] == QUOTE
				|| input[i] == DOUBLE_QUOTE))
		{
			handle_quotes(input, &i, &token, &current);
			continue ;
		}
		token_of_tokenization(input, &i, &token, &current);
		if (input[i] && is_space(input[i]))
			i++;
	}
	return (token);
}

void	append_token(t_token **token, t_token **current, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	if (!new->value)
		return ;
	new->type = find_token_type(value);
	new->next = NULL;
	if (*token == NULL)
		*token = new;
	else
		(*current)->next = new;
	*current = new;
}
