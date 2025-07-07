/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:36:10 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/07 19:23:04 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command(t_token *token)
{
	t_cmd	*curr_cmd;
	t_cmd	*head;
	t_token	*curr_token;
	int		i;

	i = 0;
	curr_token = token;
	curr_cmd = create_cmd_node(curr_token);
	if (!curr_cmd)
		return ;
	head = curr_cmd;
	process_all(&curr_cmd, &curr_token, &i);
	get_shell()->cmd = head;
}

t_cmd	*create_cmd_node(t_token *token)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = (char **)ft_calloc((count_word(token) + 1),
			(sizeof(char *)));
	if (!new_cmd->args)
		return (NULL);
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	process_all(t_cmd **cmd, t_token **token, int *i)
{
	while (*token)
	{
		if ((*token)->type == TOKEN_WORD)
			process_word(cmd, token, i);
		else if ((*token)->type == TOKEN_PIPE)
			process_pipe(cmd, token, i);
	//		else if 
	//		process_redirect(cmd, token, i);
		else
			break ;
		*token = (*token)->next;
	}
}

void	process_word(t_cmd **curr_cmd, t_token **token, int *i)
{
	(*curr_cmd)->args[*i] = ft_strdup((*token)->value);
	if (!(*curr_cmd)->args[*i])
	{
		cleanup_iteration();
		return ;
	}
	(*i)++;
}

void	process_pipe(t_cmd **cmd, t_token **token, int *i)
{
	(*cmd)->next = create_cmd_node((*token)->next);
	if (!(*cmd)->next)
		return ;
	*cmd = (*cmd)->next;
	*i = 0;
}

/*
void	process_redirect(t_cmd **cmd, t_token **token, int *i)
{
	if ((*token)->type == TOKEN_WORD && (*token)->next->type == TOKEN_REDIRIN)
	{
		if (valid_file(*token))
		{
			clenup_iteration();
			return ;
		}
		(*cmd)->infile = (*token); 
	}
	else if ((*token)->type == TOKEN_REDIROUT && (*token)->next->type == TOKEN_WORD)
	{
		if (valid_file(*token));
		{
			perror((*token->value));
			clenup_iteration();
			return ;
		}
		(*cmd)->outfile = toke->next;
	}
}

int	valid_file(t_token *token)
{
	int fd;
	if (token->next->type == TOKEN_REDIRIN)	
	{
		if (access(token->value, R_OK) == -1)
		{
			perror("");
			get_shell()->exit_status = 2;
			return (1);
		}
	}
	else if (token->type == TOKEN_REDIROUT)	
	{
		fd = opem(token->next->value, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, 0644); 
		if (fd <= -1)
		{
			perror("");
			get_shell()->exit_status = 2;
			return (1);
		}
	}
	return (0);
}
*/
