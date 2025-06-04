/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:28:11 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/04 16:25:02 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type    find_token_type(char *str)
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

t_token *tokenization(t_token *token, char *input)
{
    t_token *current;
    char    *value;
    int     i;
    int     start;

    i = 0;
    current = NULL;
    while (input[i] != '\0')
    {
        while (input[i] && ft_strchr(AVOID_TOKENS, input[i]))
            i++;
        if (input[i] == '\0')
            break ;
        if (!handle_quotes(input, &i, &token, &current))
        {
            start = i;
            while (input[i] && !ft_strchr(AVOID_TOKENS, input[i]))
                i++;
            value = ft_substr(input, start, i - start);
            append_token(&token, &current, value);
        }
    }
    return (token);
}

int handle_quotes(char *input, int *i, t_token **token, t_token **current)
{
    int     start;
    int     verify_quotes;
    char    *value;

    if (input[*i] != QUOTE && input[*i] != DOUBLE_QUOTE)
        return (0);
    verify_quotes = input[*i];
    start = ++(*i);
    while (input[*i] != verify_quotes && input[*i] != '\0')
        (*i)++;
    value = ft_substr(input, start, *i - start);
    append_token(token, current, value);
    if (input[*i] == verify_quotes)
        (*i)++;
    return (1);
}

void append_token(t_token **token, t_token **current, char *value)
{
    t_token *new;

    new = ft_calloc(1, sizeof(t_token));
    new->value = value;
    new->type = find_token_type(value);
    new->next = NULL;
    if (*token == NULL)
        *token = new;
    else
        (*current)->next = new;
    *current = new;
}

void    ft_print_token(t_token *list)
{
	while (list != NULL) 
	{
		ft_printf("token: %s         | type de token %d\n", list->value, list->type);
		list = list->next; 
	}
	return ;
}
