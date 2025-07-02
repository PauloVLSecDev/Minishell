/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:35:17 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/02 17:16:54 by brunogue         ###   ########.fr       */
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
}

void	clean_exit(int code)
{
	if (get_shell()->input)
		free(get_shell()->input);
	free_env(get_shell()->env);
	free_cmd(get_shell()->cmd);
	free_token_list(get_shell()->token);
	exit(code);
}

void cleanup_iteration()
{
    if (get_shell()->token)
    {
        free_token_list(get_shell()->token);
        get_shell()->token = NULL;
    }
    if (get_shell()->cmd)
    {
        free_cmd(get_shell()->cmd);
        get_shell()->cmd = NULL;
    }
    if (get_shell()->input)
    {
        free(get_shell()->input);
        get_shell()->input = NULL;
    }
}
