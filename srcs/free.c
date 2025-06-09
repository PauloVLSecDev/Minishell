/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:35:17 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/08 16:20:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value); // valor duplicado com ft_substr
		free(token);        // struct t_token
		token = tmp;
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;
	t_env	*next;

	temp = env;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp->name);
		free(temp->content);
		free(temp);
		temp = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}
