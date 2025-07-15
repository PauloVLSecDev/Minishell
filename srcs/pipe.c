/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */ /*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:46:45 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/14 20:24:18 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_two(int *pipefd);

static void	process_parrent(int *pipefd, int *prev_fd, int status, t_cmd *cmd);

void	execute_pipeline(t_cmd *cmd)
{
	int			pipefd[2];
	int			prev_fd;
	t_fd_backup	backup;

	backup_fds(&backup);
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
	restaure_for_origin_fds(&backup);
	close(backup.std_infile);
	close(backup.std_outfile);
	close(backup.std_err);
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
		{
			dup2(*prev_fd, STDIN_FILENO);
			close(*prev_fd);
		}
		if (cmd->next != NULL)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close_two(pipefd);
		}
		if (redir_actions(cmd))
			exit(3);
		exec_all(cmd);
		close_two(pipefd);
		exit(1);
	}
	else if (pid > 0)
	{
		process_parrent(pipefd, prev_fd, status, cmd);
		waitpid(pid, &status, 0);
	}
}

static void	process_parrent(int *pipefd, int *prev_fd, int status, t_cmd *cmd)
{
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	if (cmd->next != NULL)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
	get_shell()->exit_status = WEXITSTATUS(status);
	return ;
}

static void	close_two(int *pipefd)
{
	close(pipefd[1]);
	close(pipefd[0]);
}
