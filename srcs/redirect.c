/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:25:38 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/13 17:27:57 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_append(t_token *token);
static int	ft_append(t_cmd *cmd);

int	redir_actions(t_cmd *cmd)
{
	int	fd_in;
	int	fd_out;

	if (cmd->infile)
	{
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in == -1)
			return (1);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->outfile && cmd->append_mode == 0)
	{
		fd_out = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd_out == -1)
			return (1);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (cmd->append_mode)
	{
		if (ft_append(cmd))
			return (1);
	}
	return (0);
}

int	process_redirect(t_cmd **cmd, t_token **token)
{
	if ((*token)->type == TOKEN_REDIR_IN && (*token)->next->type == TOKEN_WORD)
		(*cmd)->infile = ft_strdup((*token)->next->value);
	else if ((*token)->type == TOKEN_REDIR_OUT && (*token)->next
		&& (*token)->next->type == TOKEN_WORD)
	{
		if (valid_file(*token))
			return (1);
		(*cmd)->outfile = ft_strdup((*token)->next->value);
	}
	else if ((*token)->type == TOKEN_APPEND
		&& (*token)->next->type == TOKEN_WORD)
	{
		if (valid_append(*token))
				return (1);
		(*cmd)->append_mode = 1;
		(*cmd)->outfile = ft_strdup((*token)->next->value);
	}
	return (0);
}

static int	valid_append(t_token *token)
{
	int		tmp_append;
	char	*append_file;

	append_file = token->next->value;
	tmp_append = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tmp_append <= -1)
		return (1);
	close(tmp_append);
	unlink(append_file);
	return (0);
}

static	int ft_append(t_cmd *cmd)
{
	int	fd_append;
	char *append_file;

	append_file = cmd->outfile;
	fd_append = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_append <= -1)
		return (1);
	dup2(fd_append, STDOUT_FILENO);
	close(fd_append);
	return (0);
}

int	valid_file(t_token *token)
{
	char	*file_name;

	file_name = token->next->value;
	if (token->type == TOKEN_REDIR_IN)
	{
		if (access(file_name, R_OK) == -1)
			return (1);
	}
	return (0);
}
