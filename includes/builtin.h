/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:04 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/23 14:38:48 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# include "minishell.h"

enum	e_builtin
{
	NOT_BUILTIN,
	ECHO,
	CD,
	PWD,
	ENV,
	EXIT,
};

//EXEC_BUILTIN
int		is_builtin(void);
int		exec_builtin(int code);
int		count_word(t_token *token);
void	token_to_cmd(void);

//FT_ECHO
int		ft_echo(char **args);

//FT_PWD
void	ft_pwd(void);

//FT_CD
int		ft_cd(char **args);

//FT_ENV
int		ft_env(char **args);

//FT_EXIT
int		ft_exit(char **args);
void	clean_exit(int code);

#endif
