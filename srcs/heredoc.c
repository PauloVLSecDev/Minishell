/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:08:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/19 21:46:08 by pvitor-l         ###   ########.fr       */
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

void	heredoc_manager(t_token *current, int fd_heredoc)
{
	char	*delimiter;

	delimiter = current->next->value;
	// valid_quotes_heredoc(delimiter);
	exec_heredoc(delimiter, fd_heredoc);
	close_all();
	exit(0);
}

void	exec_heredoc(char *delimiter, int fd_heredoc)
{
	char	*input;

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
		ft_putendl_fd(input, fd_heredoc);
	}
}

void	heredoc(t_token *token)
{
	t_token	*current;
	int		i;

	i = 0;
	current = token;
	while (current)
	{
		//if (current->type == TOKEN_HEREDOC && current->next->type == TOKEN_WORD)
		if (current->type == TOKEN_HEREDOC)
			process_heredoc(current, i);
		current = current->next;
		i++;
	}
}
