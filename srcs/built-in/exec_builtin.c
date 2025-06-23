/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/23 14:37:47 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(void)
{
    t_cmd  *cmd;
    
    cmd = get_shell()->cmd;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (-1);
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (CD);
	if (!ft_strcmp(cmd->args[0], "env"))
		return (ENV);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (EXIT);
	return (-1);
}

int exec_builtin(int code)
{
    if (code == ECHO)
        ft_echo(get_shell()->cmd->args);
    else if (code == PWD)
        ft_pwd();
    else if (code == CD)
        ft_cd(get_shell()->cmd->args);
    else if (code == ENV)
        ft_env(get_shell()->cmd->args);
    else if (code == EXIT)
        ft_exit(get_shell()->cmd->args);
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

void	token_to_cmd(void)
{
	t_token	*temp;
	int		i;
	int		count;

	if (!get_shell()->token)
		return ;
	count = count_word(get_shell()->token);
	get_shell()->cmd = malloc(sizeof(t_cmd));
	if (!get_shell()->cmd)
		return ;
	get_shell()->cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!get_shell()->cmd->args)
	{
		free(get_shell()->cmd);
		get_shell()->cmd = NULL;
		return ;
	}
	temp = get_shell()->token;
	i = 0;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
		{
			get_shell()->cmd->args[i] = ft_strdup(temp->value);
			if (!get_shell()->cmd->args[i])
			{
				while (i > 0)
					free(get_shell()->cmd->args[--i]);
				free(get_shell()->cmd->args);
				free(get_shell()->cmd);
				get_shell()->cmd = NULL;
				return ;
			}
			i++;
		}
		else
			break ;
		temp = temp->next;
	}
	get_shell()->cmd->args[i] = NULL;
	get_shell()->cmd->next = NULL;
}

/*
void	token_to_cmd(t_cmd *cmd, t_token *token)
{
	int len_nodes;
	t_cmd *parse_cmd;
	t_token *current;

	current = token;
	len_nodes = count_word;
	parse_cmd = cmd;
	parse_cmd = malloc(sizeof(t_cmd));
	parse_cmd->args = (char **)malloc((len_nodes + 1) * sizeof(char *));

	while (current)
	{
		if (current == TOKEN_PIPE)
			parse = parse->next;'
		else if (current->type == TOKEN_WORD)
		{
			parse->args[i] = ft_strdup(current->value);	
			if (
		}
	}
	
}
*/
