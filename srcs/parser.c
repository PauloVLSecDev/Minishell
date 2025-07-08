/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:53 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/07 14:11:24 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *input)
{
	int	count_quote;
	int	count_double_quote;
	int	i;

	i = 0;
	count_quote = 0;
	count_double_quote = 0;
	while (input[i] != '\0')
	{
		if (input[i] == QUOTE)
			count_quote++;
		if (input[i] == DOUBLE_QUOTE)
			count_double_quote++;
		i++;
	}
	if (!(count_quote % 2 == 0) || !(count_double_quote % 2 == 0))
	{
		get_shell()->exit_status = 2;
		return (0);
	}
	return (1);
}

int	valid_pipe(t_token *list)
{
	t_token	*head;

	head = list;
	while (list != NULL)
	{
		if (list->type == TOKEN_PIPE && list->next == NULL)
		{
			ft_printf("pipe syntax error\n");
			return (1);
		}
		else if (head->type == TOKEN_PIPE)
		{
			ft_printf("syntax error near unexpected token `|'\n");
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
		if ((list->type == TOKEN_REDIR_IN) && (list->next == NULL))
		{
			ft_printf("syntax error near unexpected token '<' \n");
			return (1);
		}
		else if (list->type == TOKEN_REDIR_IN && list->next->type != TOKEN_WORD)
		{
			ft_printf("redirect syntax error\n");
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
		if (list->type == TOKEN_REDIR_OUT && list->next == NULL)
		{
			ft_printf("syntax error near unexpected token `>'\n");
			return (1);
		}
		else if (list->type == TOKEN_REDIR_OUT
			&& list->next->type != TOKEN_WORD)
		{
			ft_printf("redirect syntax error\n");
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
		if (list->type == TOKEN_HEREDOC && list->next == NULL)
		{
			ft_printf("syntax error near unexpected token `>>'\n");
			return (1);
		}
		else if (list->type == TOKEN_HEREDOC && list->next->type != TOKEN_WORD)
		{
			ft_printf("heredoc syntax error\n");
			return (1);
		}
		list = list->next;
	}
	return (0);
}
