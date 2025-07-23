/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:28:11 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/22 15:25:07 by brunogue         ###   ########.fr       */
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

t_token	*tokenization(t_token *token, char *input, t_token *current)
{
	char	*value;
	int		i;
	int		start;
	char	*remove_quotes;
	size_t	len;

	i = 0;
	while (input[i] != '\0')
	{
		if (ft_avoid_tokens(input, &i))
			continue ;
		if (extract_redir_or_pipe(input, &i, &token, &current))
			continue ;
		if (current && current->type != TOKEN_HEREDOC)
		{
			if (handle_quotes(input, &i, &token, &current))
				continue ;
		}
		start = i;
		while ((input[i] && !ft_strchr(AVOID_TOKENS, input[i])
			&& !ft_strchr(SPECIALS_CHARS, input[i])) || (input[i] && current && current->type == TOKEN_HEREDOC))
			i++;
		if (i > start)
		{
			value = ft_substr(input, start, i - start);
            append_token(&token, &current, value);
            if (current->type == TOKEN_HEREDOC)
            {
                len = ft_strlen(current->value);
                if ((current->value[0] == '"' && current->value[len - 1] == '"') ||
                    (current->value[0] == '\'' && current->value[len - 1] == '\''))
                {  
                    current->no_expand = true;
                    remove_quotes = ft_substr(current->value, 1, len - 2);
                    free(current->value);
                    current->value = remove_quotes;
                }
            }
            free(value);			
			// value = ft_substr(input, start, i - start);
			// append_token(&token, &current, value);
			// free(value);
		}
	}
	return (token);
}

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	handle_quotes(char *input, int *i, t_token **token, t_token **current)
{
	int		start;
	char	verify_quotes;
	char	*value;
	char	*joined;
	int		quote_pos;

	if (input[*i] != QUOTE && input[*i] != DOUBLE_QUOTE)
		return (0);
	verify_quotes = input[*i];
	quote_pos = (*i)++;
	start = *i;
	while (input[*i] && input[*i] != verify_quotes)
		(*i)++;
	value = ft_substr(input, start, *i - start);
	if (*current && quote_pos > 0 && !is_space(input[quote_pos - 1]))
	{
		joined = ft_strjoin((*current)->value, value);
		free((*current)->value);
		(*current)->value = joined;
	}
	else
		append_token(token, current, value);
	free(value);
	if (input[*i] == verify_quotes)
		(*i)++;
	return (1);
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

void	ft_print_token(t_token *list)
{
	while (list != NULL)
	{
		ft_printf("token: %s         | type of token %d\n", list->value,
			list->type);
		list = list->next;
	}
	return ;
}
