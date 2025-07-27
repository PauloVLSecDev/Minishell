/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:37:32 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/19 17:26:16 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_metacharacteres(t_token *token)
{
	if (!token)
		return (0);
	if (valid_pipe(token))
	{
		ft_printf("invalid pipe |\n");
		return (1);
	}
	else if (valid_redir_in(token))
	{
		ft_printf("invalid redirect <\n");
		return (1);
	}
	else if (valid_redir_out(token))
	{
		ft_printf("invalid redirect >\n");
		return (1);
	}
	else if (valid_heredoc(token) || valid_append(token))
	{
		ft_printf("syntax error near unexpected token `<< or >> '\n");
		return (1);
	}
	return (0);
}
