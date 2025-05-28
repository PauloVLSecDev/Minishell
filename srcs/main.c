/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:04:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/05/28 17:05:52 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	const char	*name;
	char		*input;
    t_token *token_list;

	name = "Minishell> ";
	while (1)
	{
		input = readline(name);
		if (!check_quotes(input))
			ft_printf("nao contem um numero par de aspas: %s\n", input);
		if (!strcmp(input, "exit"))
			return (1);
        add_history(input);
        token_list = tokenization(input);
        valid_pipe(token_list);
		ft_printf("%s\n", input);
        ft_print_token(token_list);
        free(input);
	}
	return (0);
}

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

t_token_type    find_token_type(char *str)
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

t_token *tokenization(char *input)
{
	t_token	*new;
	t_token	*head;
    t_token *current;  
	char    *token;

	head = NULL;
    current = NULL;  
	token = ft_strtok(input, " ");
	while (token)
	{
		new = ft_calloc(1, sizeof(t_token));
		new->value = ft_strdup(token);
		new->type = find_token_type(token);
        new->next = NULL;
        if(!head)
        {
            head = new;
            current = new;
        } 
        else
        {
                current->next = new;
                current = new;
        }
		token = ft_strtok(NULL, " ");
	}
	return (head);
}

void    ft_print_token(t_token *list)
{
    while (list != NULL) 
    {
        ft_printf("token: %s   type de token %d\n", list->value, list->type);
        list = list->next; 
    }
    return ;
}
