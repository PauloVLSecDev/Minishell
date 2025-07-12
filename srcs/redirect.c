/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:25:38 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/08 20:50:56 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redirect(t_cmd **cmd, t_token **token)
{
	if ((*token)->type == TOKEN_WORD && (*token)->next->type == TOKEN_REDIR_IN)
	{
		if (valid_file(*token))
		{
			cleanup_iteration();
			return ;
		}
		(*cmd)->infile = ft_strdup((*token)->value); 
		printf ("valores %s\n", (*cmd)->infile);
	}
	else if ((*token)->type == TOKEN_REDIR_OUT && (*token)->next->type == TOKEN_WORD)
	{
		if (valid_file(*token))
		{
			perror((*token)->value);
			cleanup_iteration();
			return ;
		}
		(*cmd)->outfile = ft_strdup((*token)->value);
		printf ("valores %s \n", (*cmd)->outfile);
	}
}

int	valid_file(t_token *token)
{
	int fd;

	if (token->next->type == TOKEN_REDIR_IN)	
	{
		if (access(token->value, R_OK) == -1)
		{
			perror("");
			get_shell()->exit_status = 2;
			return (1);
		}
	}
	else if (token->type == TOKEN_REDIR_OUT)	
	{
		fd = open(token->next->value, O_WRONLY | O_TRUNC | O_CREAT, 0644); 
		if (fd <= -1)
		{
			perror("invalid fd");
			get_shell()->exit_status = 2;
			return (1);
		}
		close(fd);
	}
	return (0);
}
