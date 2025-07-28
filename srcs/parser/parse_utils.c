/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:38:41 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/23 15:06:03 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_append(t_token *token)
{
	t_token	*head;

	head = token;
	if (head->type == TOKEN_APPEND && head->next == NULL)
		return (1);
	while (head)
	{
		if (head->type == TOKEN_APPEND && head->next != NULL)
		{
			if (head->type == TOKEN_APPEND && head->next->type != TOKEN_WORD)
				return (1);
		}
		else if (head->type == TOKEN_APPEND && head->next == NULL)
			return (1);
		head = head->next;
	}
	return (0);
}
