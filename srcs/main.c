/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/04 16:27:27 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_token		*token;
    t_token 	*token_list;
	char		*input;

	token = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!check_quotes(input))
			ft_printf("nao contem um numero par de aspas: %s\n", input);
		if (!ft_strcmp(input, "exit"))
		{
			free (input);
			return (1);
		}
        add_history(input);
        token_list = tokenization(token, input);
        valid_pipe(token_list);
        ft_print_token(token_list);
        free(input);
	}
	return (0);
}
