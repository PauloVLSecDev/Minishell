/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:08:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/20 21:29:17 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredoc(t_token *current, int i, t_cmd **cmd)
{
	char	*filename;
	int		fd_heredoc;
	int		status;
	pid_t	pid;
	char *pos_fix;

	pos_fix = ft_itoa(i);
	filename = ft_strjoin("/tmp/heredoc", pos_fix);
	fd_heredoc = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	(*cmd)->infile = ft_strdup(filename);
	free(filename);
	free(pos_fix);
	pid = fork();
	if (pid == 0)
		heredoc_manager(current, fd_heredoc);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(fd_heredoc);
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

	delimiter = current->next->value;
	// valid_quotes_heredoc(delimiter);
	exec_heredoc(delimiter, fd_heredoc);
	close_all();
	exit(0);
	delimiter = ft_strdup(current->next->value);
	if (!delimiter)
	{
		close(fd_heredoc);
		exit(1);
	}
	// quotes = valid_quotes_heredoc(delimiter);
	exec_heredoc(delimiter, fd_heredoc);
	free(delimiter);
	close(fd_heredoc);
	free_env(get_shell()->env);
	cleanup_iteration();
	exit (0);
}

void	exec_heredoc(char *delimiter, int fd_heredoc)
{
	char	*input;
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
	//	if (!quotes)
	//	input = expand_var(input);
		ft_putendl_fd(input, fd_heredoc);
		free(input);
	}
}
