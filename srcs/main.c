/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/27 15:43:30 by brunogue         ###   ########.fr       */
=======
/*   Updated: 2025/05/27 16:09:00 by brunogue         ###   ########.fr       */
>>>>>>> 5c99cd2df882a5a41f7e586fc01784b46c2f9680
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	const char	*name;
	char		*input;

	name = "Minishell> ";
	while (1)
	{
		input = readline(name);
		if (!check_quotes(input))
			ft_printf("nao contem um numero par de aspas: %s\n", input);
		if (!strcmp(input, "exit"))
			return (1);
        add_history(input);
		ft_printf("%s\n", input);
        free(input);
	}
	return (0);
}

int	check_quotes(char *imput)
{
	int	count_quote;
	int	count_double_quote;
	int	i;

	i = 0;
	count_quote = 0;
	count_double_quote = 0;
	while (imput[i] != '\0')
	{
		if (imput[i] == QUOTE)
			count_quote++;
		if (imput[i] == DOUBLE_QUOTE)
			count_double_quote++;
		i++;
	}
	if (!(count_quote % 2 == 0) || !(count_double_quote % 2 == 0))
		return (0);
	return (1);
}

void	token_type()
{
	
}