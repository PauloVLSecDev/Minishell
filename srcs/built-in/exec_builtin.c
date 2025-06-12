/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/12 18:56:07 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	is_builtin(t_shell *sh)
{
	if (!sh->cmd || !sh->cmd->args || !sh->cmd->args[0])
		return (-1);
	if (!ft_strcmp(sh->cmd->args[0], "echo"))
		return (ECHO);
	if (!ft_strcmp(sh->cmd->args[0], "pwd"))
		return (PWD);
	if (!ft_strcmp(sh->cmd->args[0], "cd"))
		return (CD);
	if (!ft_strcmp(sh->cmd->args[0], "env"))
		return (ENV);
	if (!ft_strcmp(sh->cmd->args[0], "exit"))
		return (EXIT);
	return (-1);
}

int exec_builtin(t_shell *sh)
{
    int code = is_builtin(sh);

    if (code == ECHO)
        ft_echo(sh->cmd->args);
    else if (code == PWD)
        ft_pwd();
    else if (code == CD)
        ft_cd(sh->cmd->args, sh);
    else if (code == ENV)
        ft_env(sh->cmd->args, sh);
    else if (code == EXIT)
        ft_exit(sh->cmd->args, sh);

    return (code);
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


void	token_to_cmd(t_shell *sh)
{
	t_token	*temp;
	int		i;
	int		count;

	if (!sh->token)
		return ;
	count = count_word(sh->token);
	sh->cmd = malloc(sizeof(t_cmd));
	if (!sh->cmd)
		return ;
	sh->cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!sh->cmd->args)
	{
		free(sh->cmd);
		sh->cmd = NULL;
		return ;
	}
	temp = sh->token;
	i = 0;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
		{
			sh->cmd->args[i] = ft_strdup(temp->value);
			if (!sh->cmd->args[i])
			{
				while (i > 0)
					free(sh->cmd->args[--i]);
				free(sh->cmd->args);
				free(sh->cmd);
				sh->cmd = NULL;
				return ;
			}
			i++;
		}
		else
			break ;
		temp = temp->next;
	}
	sh->cmd->args[i] = NULL;
	sh->cmd->next = NULL;
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
	sh->cmd->args = malloc(sizeof(char *) * (count + 1));
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			sh->cmd->args[i] = ft_strdup(token->value);
			i++;
		}
		else
			break ;
		token = token->next;
	}
	sh->cmd->args[i] = NULL;
	cmd->next = NULL;
	return (cmd);
}
*/