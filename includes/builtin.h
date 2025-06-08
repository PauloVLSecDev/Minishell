/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:04 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/05 19:51:10 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"

enum e_builtin
{
	NOT_BUILTIN,
	ECHO,
	PWD,
	CD,
};

//EXEC_BUILTIN
int	is_builtin(char *cmd);
int	exec_builtin(t_cmd *cmd);
t_cmd	*token_to_cmd(t_token *tokens);
int	count_word(t_token *token);

//FT_ECHO
int	ft_echo(char **input);


#endif