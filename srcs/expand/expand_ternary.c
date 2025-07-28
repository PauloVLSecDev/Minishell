/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:40:08 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/28 19:41:31 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ternary(int condition, int true_val, int false_val)
{
	if (condition)
		return (true_val);
	return (false_val);
}

t_qmode	toggle_quote(char c, t_qmode in_quotes)
{
	if (c == QUOTE && in_quotes != QUOTE_DOUBLE)
		return (ternary(in_quotes == QUOTE_SINGLE, QUOTE_NONE, QUOTE_SINGLE));
	if (c == DOUBLE_QUOTE && in_quotes != QUOTE_SINGLE)
		return (ternary(in_quotes == QUOTE_DOUBLE, QUOTE_NONE, QUOTE_DOUBLE));
	return (in_quotes);
}
