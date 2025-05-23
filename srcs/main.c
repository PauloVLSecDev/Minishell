/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/05/23 16:28:06 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	const char	*name;
	char		*imput;

	name = "Minishell> ";
	while (1)
	{
		imput = readline(name);
		if (!check_quotes(imput))
			ft_printf("nao contem um numero par de aspas %s\n", imput);
		if (!strcmp(imput, "exit"))
			return (1);
		ft_printf("%s\n", imput);
	}
	return (0);
}

int check_quotes(char *imput)
{
	int	count_quote;
	int count_double_quote;
	int	i;

	i = 0;
	count_quote = 0;
    count_double_quote = 0;
	while (imput[i] != '\0')
	{
			if (imput[i] == 39)
                count_quote++; 
            if (imput[i] == 34)
                count_double_quote++; 
            i++;
	}
	if (!(count_quote % 2 == 0 ) || !(count_double_quote % 2 == 0))
        return (0); 
    return (1);
}  

