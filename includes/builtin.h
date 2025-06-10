/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:04 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/09 18:56:31 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

<<<<<<< HEAD
# ifndef PATH_MAX
#  define PATH_MAX 4096
#endif

#include "minishell.h"
=======
# include "minishell.h"
>>>>>>> init_paulo

enum	e_builtin
{
	NOT_BUILTIN,
	ECHO,
	CD,
	PWD,
};

<<<<<<< HEAD
//EXEC_BUILTIN
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_env *env);
t_cmd	*token_to_cmd(t_token *tokens);
int		count_word(t_token *token);

//FT_ECHO
int		ft_echo(char **input);
//FT_PWD
void	ft_pwd(void);
//FT_CD
int		ft_cd(char **args, t_env *env);
=======
// EXEC_BUILTIN
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd);
t_cmd	*token_to_cmd(t_token *tokens);
int		count_word(t_token *token);
>>>>>>> init_paulo

// FT_ECHO
int		ft_echo(char **input);

#endif