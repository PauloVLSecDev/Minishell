/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:46:45 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/04 19:11:00 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_cmd *cmd)
{
	int	pipefd[2];
	int	prev_fd;

	prev_fd = STDIN_FILENO;
	while (cmd != NULL)
	{
		if (pipe(pipefd) == -1)
			printf("error in creating pipe");
		create_process(pipefd, cmd, &prev_fd);
		cmd = cmd->next;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return ;
}

void	create_process(int *pipefd, t_cmd *cmd, int *prev_fd)
{
	pid_t	pid;
	int		status;

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
			close(pipefd[1]);
			close(pipefd[0]);
		}
		exec_all(cmd);
		close(pipefd[1]);
		close(pipefd[0]);
		exit(1);
	}
	else if (pid > 0)
	{
		if (*prev_fd != STDIN_FILENO)
			close(*prev_fd);
		if (cmd->next != NULL)
			close(pipefd[1]);
		*prev_fd = pipefd[0];
		waitpid(pid, &status, 0);
		get_shell()->exit_status = WEXITSTATUS(status);
	}
}
