/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:08:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/19 22:06:05 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredoc(t_token *current, int i)
{
	char	*filename;
	int		fd_heredoc;
	int		status;
	pid_t	pid;

	filename = ft_strjoin("/tmp/heredoc", ft_itoa(i));
	fd_heredoc = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
		heredoc_manager(current, fd_heredoc);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
}

int	valid_quotes_heredoc(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == DOUBLE_QUOTE || delimiter[i] == QUOTE)
			return (1);
		i++;
	}
	return (0);
}

void	heredoc_manager(t_token *current, int fd_heredoc)
{
	char	*delimiter;
	int		quotes;

	delimiter = current->next->value;
	quotes = valid_quotes_heredoc(delimiter);
	exec_heredoc(delimiter, quotes, fd_heredoc);
	close(fd_heredoc);
	exit (0);
}

void	exec_heredoc(char *delimiter, int quotes, int fd_heredoc)
{
	char *input;
	(void)fd_heredoc;

	while (1)
	{
		// signals_here()
		input = readline("> ");
		if (!input)
		{
			break ;
		}
		if (!ft_strcmp(input, delimiter))
			break ;
		if (!quotes)
			input = expand_var(input);
	}
}

void	heredoc(t_token *token)
{
	t_token *current;
	int		i;

	i = 0;
	current = token;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->next->type == TOKEN_WORD)
		{
			process_heredoc(current, i);
		}
		i++;
		current = current->next;
	}
}
