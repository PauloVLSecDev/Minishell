/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:29:22 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/11 19:40:30 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restaure_for_origin_fds(t_fd_backup *backup)
{

	if(backup->std_infile >= 0)
	{
		dup2(backup->std_infile, STDIN_FILENO);
		close(backup->std_infile);
	}
	if(backup->std_outfile >= 0)
	{
		dup2(backup->std_outfile, STDOUT_FILENO);
		close(backup->std_outfile);
	}
	if(backup->std_err >= 0)
	{
		dup2(backup->std_err, STDERR_FILENO);
		close(backup->std_err);
	}		
}

void backup_fds(t_fd_backup *backup)
{
    backup->std_infile  = -1;
    backup->std_outfile = -1;
    backup->std_err = -1;

    backup->std_infile  = dup(STDIN_FILENO);
    backup->std_outfile = dup(STDOUT_FILENO);
    backup->std_err = dup(STDERR_FILENO);
}


