/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:46:45 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/28 18:33:20 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_two(int *pipefd);
static void	process_parent(int *pipefd, int *prev_fd, int status, t_cmd *cmd);
static void	dup_for_write_pipe(int *prev_fd);

void	execute_pipeline(t_cmd *cmd)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	*pids;
	int		status;
	int		i[2];

	i[0] = 0;
	i[1] = count_cmd(cmd);
	pids = malloc(i[1] * sizeof(pid_t));
	prev_fd = STDIN_FILENO;
	while (cmd != NULL)
	{
		if (pipe(pipefd) == -1)
			printf("error in creating pipe");
		pids[i[0]] = create_child_process(pipefd, cmd, &prev_fd);
		cmd = cmd->next;
		i[0]++;
	}
	close_two(pipefd);
	close(prev_fd);
	i[0] = -1;
	while (++i[0] < i[1])
		waitpid(pids[i[0]], &status, 0);
	free(pids);
}

pid_t	create_child_process(int *pipefd, t_cmd *cmd, int *prev_fd)
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
			perror_and_exit();
		exec_all(cmd, get_shell()->env);
		free_env(get_shell()->env);
		cleanup_iteration();
		close_two(pipefd);
		exit(get_shell()->exit_status);
	}
	else if (pid > 0)
		process_parent(pipefd, prev_fd, status, cmd);
	return (pid);
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
