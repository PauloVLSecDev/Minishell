/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:17:14 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/17 20:43:12 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// STD BASH

void	on_sigint(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
void	setup_signals(void)
{
	signal(SIGINT, on_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// COMMAND SIGNAL

// 130
void	std_cmd_c(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

// 131
void	std_cmd_back_slash(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit (core dumped)\n", 20);
}
void	set_std_cmd(void)
{
	signal(SIGINT, std_cmd_c);
	signal(SIGQUIT, std_cmd_back_slash);
}

// HEREDOC SIGNAL

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
	free_cmd(get_shell()->cmd);
	free(get_shell()->cmd);
	exit(get_shell()->exit_status);
}
