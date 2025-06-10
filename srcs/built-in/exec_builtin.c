/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:05 by brunogue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/09 18:56:03 by brunogue         ###   ########.fr       */
=======
/*   Updated: 2025/06/10 16:35:10 by pvitor-l         ###   ########.fr       */
>>>>>>> init_paulo
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *input)
{
	if (!input)
		return (-1);
	if (!ft_strcmp(input, "echo"))
		return (ECHO);
	if (!ft_strcmp(input, "pwd"))
		return (PWD);
	if (!ft_strcmp(input, "cd"))
		return (CD);
	return (-1);
}

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	int	code;

	code = is_builtin(cmd->args[0]);
	if (code == ECHO)
		ft_echo(cmd->args);
	if (code == PWD)
<<<<<<< HEAD
		ft_pwd();
	if (code == CD)
		ft_cd(cmd->args, env);
	return (1);
=======
		ft_printf("PWD");
	return (code);
>>>>>>> init_paulo
}

int	count_word(t_token *token)
{
	t_token	*temp;
	int		count;

	temp = token;
	count = 0;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
			count++;
		temp = temp->next;
	}
	return (count);
}
/*
t_cmd	*token_to_cmd(t_token *token)
{
	t_cmd	*cmd;
	int		i;
	int		count;

	i = 0;
	count = count_word(token);
	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * (count + 1));
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(token->value);
			i++;
		}
		else
			break ;
		token = token->next;
	}
	cmd->args[i] = NULL;
	cmd->next = NULL;
	return (cmd);
}
*/
t_cmd	*token_to_cmd(t_token *token)
{
	t_cmd	*cmd;
	int		i;
	int		count;

	if (!token)
		return (NULL);
	count = count_word(token);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(token->value);
			if (!cmd->args[i])
			{
				while (i > 0)
					free(cmd->args[--i]);
				free(cmd->args);
				free(cmd);
				return (NULL);
			}
			i++;
		}
		else
			break ;
		token = token->next;
	}
	cmd->args[i] = NULL;
	cmd->next = NULL;
	return (cmd);
}

