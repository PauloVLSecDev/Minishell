/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:36:10 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/27 19:39:07 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_command(t_token *token)
{
	t_cmd *curr_cmd;
    t_cmd *head;      
	t_token *curr_token;
    int i;

    i = 0;
	curr_token = token;
	curr_cmd = create_cmd_node(curr_token);
    head = curr_cmd;
    if (!curr_cmd)
        return ;
    process_all(&curr_cmd, &curr_token, &i);
    curr_cmd->args[i] = NULL;
    get_shell()->cmd = head;;
}

t_cmd   *create_cmd_node(t_token *token)
{
    t_cmd * new_cmd;
    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return (NULL);
    new_cmd->args = (char **)malloc((count_word(token) + 1) * (sizeof(char *)));
	new_cmd->args[0] = NULL;
    if (!new_cmd->args)
        return (NULL);
    new_cmd->input_file = NULL;
    new_cmd->output_file = NULL;
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
        else
            break ;
        *token = (*token)->next;
    }
}

void	process_word(t_cmd **curr_cmd, t_token **token, int *i)
{
        (*curr_cmd)->args[*i] = ft_strdup((*token)->value); 
        if (!(*curr_cmd)->args[*i])
            return ; 
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
