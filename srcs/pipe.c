/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:46:45 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/01 13:08:26 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe(t_cmd *cmd)
{
	pid_t pid;
	int pipefd[2];
	int prev_fd;
    
	prev_fd = -1;
	while (cmd->next != NULL)
	{
		if (pipe(pipefd) == -1)
		{
			perror("error in creating pipe");
			return ;
		}
		pid = fork();
		children_process(&prev_fd, pid, cmd, pipefd);
		parent_process(&prev_fd, pid, cmd, pipefd);
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	while (wait(NULL) > 0);
}

void	children_process(int *prev_fd, pid_t pid, t_cmd *cmd, int *pipefd)
{
		if (pid == 0)
		{
			if ((*prev_fd) != -1)
			{
				dup2(*prev_fd, STDIN_FILENO);
				close(*prev_fd);
			}
			if (cmd->next != NULL)
			{
				dup2(pipefd[1], STDOUT_FILENO);		
				close(pipefd[1]);
				*prev_fd = pipefd[0];
			}
			exec_all(cmd);
			exit(get_shell()->exit_status);
		}
		else 
			return ;
}

void	parent_process(int *prev_fd, pid_t pid, t_cmd *cmd, int *pipefd)
{
        if (pid > 0)
		{
			if ((*prev_fd) != -1)
				close(*prev_fd);
			if (cmd->next != NULL)
			{
				close(pipefd[1]);
				(*prev_fd) = pipefd[0];
			}
		}
		else
			return ;
}
