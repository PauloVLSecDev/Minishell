/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:28:11 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/27 15:54:58 by brunogue         ###   ########.fr       */
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

// static int is_space(char c)
// {
// 	return (c == ' '  || c == '\t' || c == '\n' ||
// 			c == '\v' || c == '\f' || c == '\r');
// }

// int handle_quotes(char *input, int *i, t_token **token, t_token **current)
// {
//     int		quote_pos;
//     char	delim;
//     char	*value;
//     int		end_pos;
//     char	*joined;

// 	quote_pos = *i;
//     delim = input[*i];
//     (*i)++;
//     while (input[*i] && input[*i] != delim)
//         (*i)++;
//     end_pos = *i;
//     if (input[*i] == delim)
//         (*i)++;
//     value = ft_substr(input, quote_pos, end_pos - quote_pos + 1);
//     if (*current && quote_pos > 0 
// 		&& !is_space(input[quote_pos - 1]))
//     {
//         joined = ft_strjoin((*current)->value, value);
//         free((*current)->value);
//         (*current)->value = joined;
//     }
//     else
//         append_token(token, current, value);
//     free(value);
//     return (1);
// }
static int is_space(char c)
{
    return (c == ' '  || c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' || c == '\r');
}

int handle_quotes(char *input, int *i, t_token **token, t_token **current)
{
    char    delim     = input[*i];      // ' ou "
    int     quote_pos = *i;             // posição da aspa de abertura
    int     start;
    char   *segment;
    char   *joined;

    (*i)++;                         // pula a aspa de abertura
    start = *i;
    while (input[*i] && input[*i] != delim)
        (*i)++;
    segment = ft_substr(input, start, *i - start);
    if (input[*i] == delim)
        (*i)++;                         // pula a aspa de fechamento

    // Se antes da aspa havia um espaço (ou é o começo da linha),
    // COMEÇA um token novo. Caso contrário, ANEXA ao current.
    if (quote_pos == 0 || is_space(input[quote_pos - 1]) || *current == NULL)
    {
        append_token(token, current, segment);
    }
    else
    {
        joined = ft_strjoin((*current)->value, segment);
        free((*current)->value);
        (*current)->value = joined;
    }

    free(segment);
    return 1;
}


// t_token *tokenization(t_token *token, char *input, t_token *current)
// {
// 	char	*value;
//     int		start;
//     int		i;

//     i = 0;
//     // get_shell()->has_quotes_or_not = 0;
//     while (input[i])
//     {
//         if (ft_avoid_tokens(input, &i))
//             continue;
//         if (extract_redir_or_pipe(input, &i, &token, &current))
//             continue;
//         if (input[i] == '\'' || input[i] == '\"')
//         {
//             // get_shell()->has_quotes_or_not = 1;
//             handle_quotes(input, &i, &token, &current);
//             continue;
//         }
//         start = i;
//         while (input[i]
//                && !ft_strchr(AVOID_TOKENS,   input[i])
//                && !ft_strchr(SPECIALS_CHARS, input[i]))
//             i++;
//         if (i > start)
//         {
//             value = ft_substr(input, start, i - start);
//             append_token(&token, &current, value);
//             free(value);
//         }
//     }
//     return (token);
// }





t_token *tokenization(t_token *token, char *input, t_token *current)
{
    char *value;
    int   i = 0;
    int   start;
	char *joined;

    while (input[i])
    {
        if (ft_avoid_tokens(input, &i))
            continue;
        if (extract_redir_or_pipe(input, &i, &token, &current))
            continue;
        if (current && (input[i] == '\'' || input[i] == '"'))
        {
            handle_quotes(input, &i, &token, &current);
            continue;
        }
        start = i;
        while (input[i]
               && !ft_strchr(AVOID_TOKENS,   input[i])
               && !ft_strchr(SPECIALS_CHARS, input[i])
               && !(is_space(input[i])))
            i++;
        if (i > start)
        {
            value = ft_substr(input, start, i - start);
            if (start == 0
                || is_space(input[start - 1])
                || current == NULL)
            {
                append_token(&token, &current, value);
            }
            else
            {
                joined = ft_strjoin(current->value, value);
                free(current->value);
                current->value = joined;
            }
            free(value);
        }
        if (input[i] && is_space(input[i]))
            i++;
    }
    return token;
}

// int	handle_quotes(char *input, int *i, t_token **token, t_token **current)
// {
// 	int		start;
// 	char	verify_quotes;
// 	char	*value;
// 	char	*joined;
// 	int		quote_pos;

// 	if (input[*i] != QUOTE && input[*i] != DOUBLE_QUOTE)
// 		return (0);
// 	verify_quotes = input[*i];
// 	quote_pos = (*i)++;
// 	start = *i;
// 	while (input[*i] && input[*i] != verify_quotes)
// 		(*i)++;
// 	value = ft_substr(input, start, *i - start);
// 	if (*current && quote_pos > 0 && !is_space(input[quote_pos - 1]))
// 	{
// 		joined = ft_strjoin((*current)->value, value);
// 		free((*current)->value);
// 		(*current)->value = joined;
// 	}
// 	else
// 		append_token(token, current, value);
// 	free(value);
// 	if (input[*i] == verify_quotes)
// 		(*i)++;
// 	return (1);
// }

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
