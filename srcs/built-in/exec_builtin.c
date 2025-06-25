/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:05 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/25 19:04:21 by pvitor-l         ###   ########.fr       */
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

void	handle_command(t_token *token)
{
	t_cmd *curr_cmd;
    t_cmd *head;      
	t_token *current;
    int i;

    i = 0;
	current = token;
	curr_cmd = create_cmd_node(current);
    head = curr_cmd;
    if (!curr_cmd)
        return ;
    while (current)
	{
        if (current->type == TOKEN_WORD)
		{
            curr_cmd->args[i] = ft_strdup(current->value); 
            if (!curr_cmd->args[i])
                return ;                
            i++; 
		}
        else if (current->type == TOKEN_PIPE)
        {
            curr_cmd->next = create_cmd_node(current);
            curr_cmd = curr_cmd->next; 
            i = 0;
        }
	    else 
            break ;
        current = current->next;
	}
    curr_cmd->args[i] = NULL;
    get_shell()->cmd =  head;;
}

t_cmd *create_cmd_node(t_token *token)
{
    t_cmd * new_cmd;
    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return (NULL);
    new_cmd->args = (char **)malloc((count_word(token) + 1) * (sizeof(char *)));
    if (!new_cmd->args)
        return (NULL);
    new_cmd->input_file = NULL;
    new_cmd->output_file = NULL;
    new_cmd->next = NULL;
    return (new_cmd);
}

/*
void    redirect_command(t_token *current, t_cmd *curr_cmd)
{
   if (current->type == TOKEN_REDIRIN) 
        curr_cmd->input_file = valid_redirect(current->next->value);
   else if (current->type == TOKEN_REDIROUT) 
        curr_cmd->output_file = valid_redirect(current->next->value);
   else 
   {
        curr_cmd->input_file = 0;
        curr_cmd->output_file = 1;
   }

}

int     is_valid(char *file)
{
    int fd = open("file", );



}

*/


