/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:53 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/19 16:37:05 by pvitor-l         ###   ########.fr       */
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
	if (head->type == TOKEN_PIPE)
		return (1);
	while (head != NULL)
	{
		if (head->type == TOKEN_PIPE && head->next == NULL)
		{
			get_shell()->exit_status = 2;
			return (1);
		}
		else if (head->type == TOKEN_PIPE && head->next != NULL)
		{
			if (head->next->type == TOKEN_PIPE)
			{
				get_shell()->exit_status = 2;
				return (1);
			}
		}
		head = head->next;
	}
	return (0);
}

int	valid_redir_in(t_token *list)
{
	t_token	*head;

	head = list;
	if (head == NULL)
		return (1);
	while (head != NULL)
	{
		if ((head->type == TOKEN_REDIR_IN) && (head->next == NULL))
		{
			get_shell()->exit_status = 2;
			return (1);
		}
		else if (head->type == TOKEN_REDIR_IN && head->next->type != TOKEN_WORD)
		{
			get_shell()->exit_status = 2;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	valid_redir_out(t_token *list)
{
	t_token	*head;

	head = list;
	if (head == NULL)
		return (1);
	while (head != NULL)
	{
		if (head->type == TOKEN_REDIR_OUT && head->next == NULL)
		{
			get_shell()->exit_status = 2;
			return (1);
		}
		else if (head->type == TOKEN_REDIR_OUT
			&& head->next->type != TOKEN_WORD)
		{
			get_shell()->exit_status = 2;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	valid_heredoc(t_token *list)
{
	t_token	*head;

	head = list;
	if (head == NULL)
		return (1);
	while (head != NULL)
	{
		if (head->type == TOKEN_HEREDOC && head->next == NULL)
		{
			get_shell()->exit_status = 2;
			return (1);
		}
		else if (head->type == TOKEN_HEREDOC && head->next->type != TOKEN_WORD)
		{
			get_shell()->exit_status = 2;
			return (1);
		}
		head = head->next;
	}
	return (0);
}
