/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:17:05 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/21 20:44:16 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_heredoc(t_token **curr);

char	*ft_join_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*together_all;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	together_all = ft_strjoin(tmp, s3);
	free(tmp);
	if (!together_all)
		return (NULL);
	return (together_all);
}

int	count_word(t_token *token)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = token;
	while (curr && curr->type != TOKEN_PIPE)
	{
		if (curr->type == TOKEN_WORD)
			count++;
		else if (curr->type == TOKEN_HEREDOC)
		{
			if (is_heredoc(&curr))
				continue ;
		}
		else if (curr->type == TOKEN_REDIR_IN || curr->type == TOKEN_REDIR_OUT
			|| curr->type == TOKEN_APPEND)
		{
			curr = curr->next;
			if (curr)
				curr = curr->next;
			continue ;
		}
		curr = curr->next;
	}
	return (count);
}

int	is_heredoc(t_token **curr)
{
	(*curr) = (*curr)->next;
	if ((*curr) && (*curr)->type == TOKEN_WORD)
	{
		(*curr) = (*curr)->next;
		return (1);
	}
	return (0);
}

void	handle_heredoc(t_token **token, int *hd_counter, t_cmd **cmd)
{
	process_heredoc(*token, ++(*hd_counter), cmd);
	if ((*token)->next)
		*token = (*token)->next;
	if (*token)
		*token = (*token)->next;
}

void	add_in_outfile(t_cmd **cmd, char *filename)
{
	if ((*cmd)->outfile)
		free((*cmd)->outfile);
	(*cmd)->outfile = ft_strdup(filename);
}
