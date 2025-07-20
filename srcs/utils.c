/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:17:05 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/07/20 18:40:59 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
int	count_word(t_token *token)
{
	t_token	*temp;
	int		count;

	temp = token;
	count = 0;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
			count++;
		else if (temp->type == TOKEN_PIPE)
			break ;
		else if (temp->type == TOKEN_REDIR_IN || temp->type == TOKEN_REDIR_OUT
			|| temp->type == TOKEN_APPEND || temp->type == TOKEN_HEREDOC )
		{
			temp = temp->next;
			if (temp == NULL)
				break ;
		}
		temp = temp->next;
	}
	return (count);
}
*/

int	count_word(t_token *token)
{
	int count = 0;
	t_token *current = token;

	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD)
			count++;
		else if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			if (current && current->type == TOKEN_WORD) // This should be the delimiter
			{
				current = current->next;
				continue; // Continue to the next token after the delimiter
			}
		}
		else if (current->type == TOKEN_REDIR_IN ||
		         current->type == TOKEN_REDIR_OUT ||
		         current->type == TOKEN_APPEND)
		{
			current = current->next; // Skip the operator
			if (current)
				current = current->next; // Skip the filename
			continue; // Continue to the next token
		}
		current = current->next;
	}
	return count;
}
