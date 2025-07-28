/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:17:14 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/27 21:07:40 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	on_sigint(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signals_ctrl_c(void)
{
	signal(SIGINT, on_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	std_cmd_c(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

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
