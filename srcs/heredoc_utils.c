/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:16:38 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/26 21:17:32 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_heredoc(void)
{
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	write(STDOUT_FILENO, "\n", 1);
	get_shell()->heredoc_counter = -1;
	cleanup_iteration();
	free_env(get_shell()->env);
	exit(130);
}

void	close_all(void)
{
	int	i;

	i = 3;
	while (i <= 1024)
	{
		close(i);
		i++;
	}
}
