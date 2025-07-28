/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:08:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/28 18:54:17 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hd_parent_heredoc(pid_t pid, int status, int fd_heredoc);

void	process_heredoc(t_token *current, int i, t_cmd **cmd)
{
	char	*filename;
	int		fd_heredoc;
	int		status;
	pid_t	pid;
	char	*pos_fix;

	status = 0;
	pos_fix = ft_itoa(i);
	filename = ft_strjoin("/tmp/heredoc", pos_fix);
	fd_heredoc = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((*cmd)->infile)
		free((*cmd)->infile);
	(*cmd)->infile = ft_strdup(filename);
	free(filename);
	free(pos_fix);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signals_heredoc();
		heredoc_manager(current, fd_heredoc);
	}
	if (pid > 0)
		hd_parent_heredoc(pid, status, fd_heredoc);
}

static void	hd_parent_heredoc(pid_t pid, int status, int fd_heredoc)
{
	waitpid(pid, &status, 0);
	close(fd_heredoc);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		get_shell()->exit_status = 130;
		get_shell()->must_execute = 1;
	}
	return ;
}

int	valid_quotes_heredoc(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\"' || delimiter[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	heredoc_manager(t_token *current, int fd_heredoc)
{
	char	*delimiter;
	int		quotes;

	delimiter = ft_strdup(current->next->value);
	quotes = valid_quotes_heredoc(delimiter);
	if (!delimiter)
	{
		close(fd_heredoc);
		exit(1);
	}
	exec_heredoc(delimiter, quotes, fd_heredoc);
	free(delimiter);
	close(fd_heredoc);
	free_env(get_shell()->env);
	cleanup_iteration();
	exit(0);
}

void	exec_heredoc(char *delimiter, int quotes, int fd_heredoc)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_printf("warning: here-document at line 22 delimited"
				"by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (!ft_strcmp(input, delimiter))
			break ;
		if (quotes == 0)
			input = expand_var(input, NULL);
		ft_putendl_fd(input, fd_heredoc);
		free(input);
	}
}
