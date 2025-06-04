/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:53 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/02 15:33:35 by brunogue         ###   ########.fr       */
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
		return (0);
	return (1);
}

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
