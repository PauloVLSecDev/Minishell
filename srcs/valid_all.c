/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:37:32 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/07 13:45:57 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1 erro pipe
// 2 erro redir in
// 3 error redir out
// 4 error heredoc

int	valid_metacharacteres(t_token *token)
{
	if (valid_pipe(token))
			return (1);
	else if (valid_redir_in(token))
			return (2);
	else if (valid_redir_out(token))
			return (3);
	else if (valid_heredoc(token))
			return (4);
	return (0);
}
