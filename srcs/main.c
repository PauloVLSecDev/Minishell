/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/27 17:12:15 by pvitor-l         ###   ########.fr       */
=======
/*   Updated: 2025/05/27 20:22:12 by brunogue         ###   ########.fr       */
>>>>>>> 5480673dd4586a90351f1d538443a5e304ea1a41
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

int	validate_types(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (TOKEN_PIPE);
	if (!ft_strcmp(str, "<"))
		return (TOKEN_REDIR_IN);
	if (!ft_strcmp(str, ">"))
		return (TOKEN_REDIR_OUT);
	if (!ft_strcmp(str, "<<"))
		return (TOKEN_APPEND);
	else
		return (TOKEN_WORD);
}

void	type_correct(char *input)
{
	t_token	*new;
	char	*token;

	token = ft_strtok(input, " ");
	if (!token)
		return ;
	while (token)
	{
		new = ft_calloc(1, sizeof(t_token));
		new->value = ft_strdup(token);
		new->type = validate_types(token);
		token = ft_strtok(NULL, " ");
	}
	return ;
}
