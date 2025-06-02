/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:53 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/02 17:36:15 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_pipe(t_token *list)
{
	if (list == NULL)
		return (1);
	if (list->type == TOKEN_PIPE)
	{
		ft_printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	while (list != NULL)
	{
		if (list->type == TOKEN_PIPE && list->next->type == TOKEN_PIPE)
		{
			ft_printf("syntax error near unexpected token `||'\n");
			return (1);
		}
		else if (list->type == TOKEN_PIPE && list->next == NULL)
		{
			ft_printf("pipe syntax error\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int	valid_redir_in(t_token *list)
{
    if (list == NULL)
        return (1);
	while (list != NULL)
	{
		if (list->type == TOKEN_REDIR_IN && list->next == NULL);
		{
			ft_printf("syntax error near unexpected token `<'\n");
			return (1);
		}
		else if (list->type == TOKE_REDIR_IN && list->next->type != TOKEN_WORD)
		{
			ft_printf("pipe syntax error\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int	valid_redir_out(t_token *list)
{
    if (list == NULL)
        return (1);
	while (list != NULL)
	{
		if (list->type == TOKEN_REDIR_OUT && list->next == NULL);
		{
			ft_printf("syntax error near unexpected token `>'\n");
			return (1);
		}
		else if (list->type == TOKE_REDIR_OUT && list->next->type != TOKEN_WORD)
		{
			ft_printf("pipe syntax error\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int	valid_heredoc(t_token *list)
{
    if (list == NULL)
        return (1);
	while (list != NULL)
	{
		if (list->type == TOKEN_HEREDOC && list->next == NULL);
		{
			ft_printf("syntax error near unexpected token `>'\n");
			return (1);
		}
		else if (list->type == TOKE_HEREDOC && list->next->type != TOKEN_WORD)
		{
			ft_printf("pipe syntax error\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}
