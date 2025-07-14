/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:37:32 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/08 17:41:58 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1 erro pipe
// 2 erro redir in
// 3 error redir out
// 4 error heredoc

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
		return (2);
	}
	else if (valid_redir_out(token))
	{
		ft_printf("invalid redirect >\n");
		return (3);
	}
	else if (valid_heredoc(token))
	{
		ft_printf("invalid heredoc <<\n");
		return (4);
	}
	return (0);
}
