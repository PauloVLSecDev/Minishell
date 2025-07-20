/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:25:38 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/20 16:35:38 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_append(t_cmd *cmd);

int	redir_actions(t_cmd *cmd)
{
	int	fd_in;
	int	fd_out;

	if (cmd->infile)
	{
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in < 0)
			return (1);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->outfile && cmd->append_mode == 0)
	{
		fd_out = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd_out < 0)
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

int	process_redirect(t_cmd **cmd, t_token **token, char *filename)
{
	int		fd;

	filename = (*token)->next->value;
	if ((*token)->type == TOKEN_REDIR_OUT)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			free((*cmd)->outfile);
			(*cmd)->outfile = ft_strdup(filename);
			return (1);
		}
		close(fd);
		if ((*cmd)->outfile)
			free((*cmd)->outfile);
		(*cmd)->outfile = ft_strdup(filename);
	}
	else if ((*token)->type == TOKEN_APPEND)
	{
		(*cmd)->append_mode = 1;
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			free((*cmd)->outfile);
			(*cmd)->outfile = ft_strdup(filename);
			return (1);
		}
		close(fd);
		if ((*cmd)->outfile)
			free((*cmd)->outfile);
		(*cmd)->outfile = ft_strdup(filename);
	}
	else if ((*token)->type == TOKEN_REDIR_IN)
	{
		if (valid_file(filename, cmd))
			return (1);
	}
	return (0);
}

static int	ft_append(t_cmd *cmd)
{
	int		fd_append;
	char	*append_file;

	append_file = cmd->outfile;
	fd_append = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_append <= -1)
		return (1);
	dup2(fd_append, STDOUT_FILENO);
	close(fd_append);
	return (0);
}

int	valid_file(char *filename, t_cmd **cmd)
{
	if (access(filename, R_OK) == -1)
	{
		if ((*cmd)->infile)
			free((*cmd)->infile);
		(*cmd)->infile = ft_strdup(filename);
		return (1);
	}
	if ((*cmd)->infile)
		free((*cmd)->infile);
	(*cmd)->infile = ft_strdup(filename);
	return (0);
}
