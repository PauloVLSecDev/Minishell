/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:36:10 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/27 17:03:46 by pvitor-l         ###   ########.fr       */
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
	{
		cleanup_iteration();
		return ;
	}
	head = curr_cmd;
	process_all(&curr_cmd, &curr_token, &i);
	get_shell()->cmd = head;
}

t_cmd	*create_cmd_node(t_token *token)
{
	t_cmd	*new_cmd;
	int		word_count;

	if (!token)
		return (NULL);
	word_count = count_word(token);
	if (word_count < 0)
		return (NULL);
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->next = NULL;
	new_cmd->append_mode = 0;
	new_cmd->args = (char **)ft_calloc((word_count + 1), sizeof(char *));
	if (!new_cmd->args)
	{
		free(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

void	process_all(t_cmd **cmd, t_token **to, int *i)
{
	while (*to)
	{
		if ((*to)->type == TOKEN_HEREDOC)
		{
			get_shell()->heredoc_counter += 1;
			handle_heredoc(to, &(get_shell()->heredoc_counter), cmd);
			continue ;
		}
		else if ((*to)->type == TOKEN_WORD)
			process_word(cmd, to, i);
		else if ((*to)->type == TOKEN_PIPE)
			process_pipe(cmd, to, i);
		else if ((*to)->type == TOKEN_REDIR_IN || (*to)->type == TOKEN_REDIR_OUT
			|| (*to)->type == TOKEN_APPEND)
		{
			if (process_redirect(cmd, to, (*to)->next->value))
				break ;
			if (*to && (*to)->next)
				*to = (*to)->next;
		}
		if (*to)
			*to = (*to)->next;
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
