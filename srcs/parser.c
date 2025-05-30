/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:53 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/05/28 20:23:37 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int valid_pipe(t_token *list)
{
    while (list != NULL)
    {
        if (list->type == TOKEN_PIPE && list->next == NULL)
        {
            ft_printf("\npipe syntax error\n"); 
            return (1);
        }
        else if (list->type == TOKEN_PIPE) 
        {
            ft_printf("\nsyntax error near unexpected token `|'\n"); 
            return (1);
        }
            list = list->next;
    }
     return (0);
}
