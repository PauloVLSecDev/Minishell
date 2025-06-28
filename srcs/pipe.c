/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:46:45 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/27 19:59:18 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe(t_cmd *cmd)
{
	pid_t pid;
	int pipefd[2];
	int prev_fd;
    
	prev_fd = -1;
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
		{
			if (pipe(pipefd) == -1)
			{
				perror("error in creating pipe");
				return ;
			}
		}
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->next != NULL)
			{
				dup2(pipefd[1], STDOUT_FILENO);		
				close(pipefd[1]);
				close(pipefd[0]);
				prev_fd = pipefd[0];
			}
			exec_all(cmd);
			exit(get_shell()->exit_status);
		}
        else if (pid > 0)
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next != NULL)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
		}
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	while (wait(NULL) > 0);
}
