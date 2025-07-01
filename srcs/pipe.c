/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:46:45 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/06/30 20:55:11 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_cmd *cmd)
{
		int	pipefd[2];

		int 	prev_fd;

		prev_fd = STDIN_FILENO;

		while (cmd != NULL)
		{
			if (pipe(pipefd) == -1)
				printf("error in creating pipe");
			create_process(pipefd, cmd, &prev_fd);
			cmd = cmd->next;
		}
	return ;
}

void	create_process(int *pipefd, t_cmd *cmd, int *prev_fd)
{
		pid_t pid;
		
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
			exit(1);
		}
		else 
		{
			if (*prev_fd != STDIN_FILENO)
				close(*prev_fd);
			if (cmd->next != NULL)\
				close(pipefd[1]);
			*prev_fd = pipefd[0];
		}
}
