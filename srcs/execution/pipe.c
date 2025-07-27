/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:46:45 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/26 19:38:46 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_two(int *pipefd);
static void	process_parent(int *pipefd, int *prev_fd, int status, t_cmd *cmd);
static void	dup_for_write_pipe(int *prev_fd);

void	execute_pipeline(t_cmd *cmd)
{
	int	pipefd[2];
	int	prev_fd;

	prev_fd = STDIN_FILENO;
	while (cmd != NULL)
	{
		if (pipe(pipefd) == -1)
			printf("error in creating pipe");
		create_child_process(pipefd, cmd, &prev_fd);
		cmd = cmd->next;
	}
	close_two(pipefd);
	close(prev_fd);
	return ;
}

void	create_child_process(int *pipefd, t_cmd *cmd, int *prev_fd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (*prev_fd != STDIN_FILENO)
			dup_for_write_pipe(prev_fd);
		if (cmd->next != NULL)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close_two(pipefd);
		}
		if (redir_actions(cmd))
			exit(get_shell()->exit_status);
		exec_all(cmd, get_shell()->env);
		free_env(get_shell()->env);
		cleanup_iteration();
		close_two(pipefd);
		exit(get_shell()->exit_status);
	}
	else if (pid > 0)
		process_parent(pipefd, prev_fd, status, cmd);
	waitpid(pid, &status, 0);
}

static void	process_parent(int *pipefd, int *prev_fd, int status, t_cmd *cmd)
{
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	if (cmd->next != NULL)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
	get_shell()->exit_status = WEXITSTATUS(status);
	return ;
}

void	dup_for_write_pipe(int *prev_fd)
{
	if (dup2(*prev_fd, STDIN_FILENO) == -1)
		printf("error in dup2 in trying write in pipe");
	close(*prev_fd);
}

static void	close_two(int *pipefd)
{
	close(pipefd[1]);
	close(pipefd[0]);
}
