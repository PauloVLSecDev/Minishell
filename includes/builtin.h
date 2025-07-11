/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:04 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/11 20:00:58 by brunogue         ###   ########.fr       */
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
	EXPORT,
	EXIT,
};

// EXEC_BUILTIN
int		is_builtin(char **args);
int		exec_builtin(int codem, t_cmd *cmd);
int		count_word(t_token *token);
void	token_to_cmd(void);

// FT_ECHO
int		ft_echo(char **args);
void	ambient_var(char *arg, t_env *env, int has_next);

// FT_PWD
int		ft_pwd(void);

// FT_CD
int		ft_cd(char **args);

// FT_ENV
int		ft_env(char **args);


// FT_EXIT
int		ft_exit(char **args);
void	clean_exit(int code);

/*   EXPORT   */

// FT_EXPORT
void	print_export(void);
int		ft_export(char **args);
void	valid_export(char **args, int *i);
void	add_env_node(char *name, char *value);
void	update_node(t_env *node, char *value);


//EXPORT_UTILS
void	ft_error_export(char *name);
void	ft_swap_str(char **i, char **j);
t_env	*find_env_node(char *name);

// VALIDS_EXPORT
int		is_valid_identifier(char *name);
int		error_identifier(char *name, char *value);
void	correct_identifier(char *name, char *value);

#endif
