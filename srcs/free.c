/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:35:17 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/17 14:46:32 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->name);
		free(env->content);
		free(env);
		env = temp;
	}
}

void	free_cmd(t_cmd *cmd)
{

    t_cmd *tmp;

    while (cmd != NULL)
    {
        tmp = cmd->next;
        free_all(cmd->args);
        free(cmd);
        cmd = tmp;
    }
    return ;
}

void	clean_exit(t_shell *sh, int code)
{
	if (sh->input)
		free(sh->input);
	free_env(sh->env);
	free_cmd(sh->cmd);
	free_token_list(sh->token);
    free(sh);
	exit(code);
}

void cleanup_iteration(t_shell *sh)
{
    if (sh->token)
    {
        free_token_list(sh->token);
        sh->token = NULL;
    }
    if (sh->cmd)
    {
        free_cmd(sh->cmd);
        sh->cmd = NULL;
    }
    if (sh->input)
    {
        free(sh->input);
        sh->input = NULL;
    }
}
