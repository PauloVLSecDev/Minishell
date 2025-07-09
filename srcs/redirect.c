/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:25:38 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/09 17:00:49 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_actions(t_cmd *cmd)
{
	int fd_in;
	int fd_out;

	if (cmd->infile)
	{
		fd_in = open(cmd->infile,	R_DONLY); 
		if (fd == -1)
			return (1);
		dup2(fd_in, STDIN_FILENO)l
	}
	else if (cmd->outfile)
	{
		fd_out = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644); 
		if (fd == -1)
			return (1);
		dup2(fd_out, STDOUT_FILENO);
	}
	else if (cmd->append_mode)
		append_function(cmd);
	return (0);
}

int	process_redirect(t_cmd **cmd, t_token **token)
{
	if ((*token)->type == TOKEN_REDIR_IN && (*token)->next->type == TOKEN_WORD )
	{
		if (valid_file(*token))
			return (1);
		(*cmd)->infile = ft_strdup((*token)->next->value); 
	}
	else if ((*token)->type == TOKEN_REDIR_OUT (*token)->next && (*token)->next->type == TOKEN_WORD)
	{
		if (valid_file(*token))
			return (1);
		(*cmd)->outfile = ft_strdup((*token)->next->value);
	}
	else if (*token)->type == TOKEN_APPEND && (*token)->next->type == TOKEN_WORD)
	{
		if (valid_append(*token)

				(*cmd)->append_mode = 1;
	}
	return (0);
}

static int	valid_append(t_token *token)
{
	int tmp_append;
	char *append_file;

	append_file = token->next->value;
	tmp_append = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (tmp_append == -1)
		return (1);
	close(tmp_append);
	unlink(append_file);

}

static ft_append(t_cmd *cmd)
{
	tmp_append = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	//esta funcao inda esta inacaba testarei tanto o redirect in quanto o redirect out e o append, todas juntas)
}

int	valid_file(t_token *token)

{
	int tmp_fd;
	char *file_name;

	file_name = token->next->value;
	if (token->type == TOKEN_REDIR_IN)
	{
		if (access(file_name, F_OK | R_OK) == -1)
			return (1);
	}
	else if (token->type == TOKEN_REDIR_OUT)
	{
		if (access(file_name, F_OK) 
				return (0);
		else 
		{
			tmp_fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0644); 
			if (tmp_fd == -1)
				return (1);
			close(tmp_fd);
			unlink(file_name);
		}
	}
	return (0);
}
