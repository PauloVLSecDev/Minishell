/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:04 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/12 20:08:34 by pvitor-l         ###   ########.fr       */
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
int		is_builtin(t_shell *sh);
int		exec_builtin(t_shell *sh);
int		count_word(t_token *token);
void	token_to_cmd(t_shell *sh);

//FT_ECHO
int		ft_echo(char **args);

//FT_PWD
void	ft_pwd(void);

//FT_CD
int		ft_cd(char **args, t_shell *sh);

//FT_ENV
int		ft_env(char **args, t_shell *sh);

//FT_EXIT
int		ft_exit(char **args, t_shell *sh);
void	clean_exit(t_shell *sh, int code);

#endif
