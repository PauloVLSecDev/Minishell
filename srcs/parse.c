/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:53 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/05/28 16:58:41 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int valid_pipe(t_token *list)
{
    t_token *head;

    head = list;
     while (list != NULL)
     {
            if (head->type == TOKEN_PIPE) 
            {
                ft_printf("syntax error near unexpected token `|'\n"); 
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
