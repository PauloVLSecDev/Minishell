/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:54:23 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/28 18:59:39 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*curr;
	int		count_cmd;

	curr = cmd;
	count_cmd = 0;
	if (!curr)
		return (0);
	while (curr != NULL)
	{
		count_cmd++;
		curr = curr->next;
	}
	return (count_cmd);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	perror_and_exit(void)
{
	perror("");
	exit(get_shell()->exit_status);
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
