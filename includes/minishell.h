/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:55:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/11 12:58:36 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../libft/libft.h"
# include "struct.h"
# include "builtin.h"
# include "parser.h"
# include "token.h"
// LIBS
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define AVOID_TOKENS " \t\r\v\f"
# define QUOTE '\''
# define DOUBLE_QUOTE '"'

// token.c
t_token_type	find_token_type(char *str);
t_token			*tokenization(t_token *token, char *input);
int				handle_quotes(char *input, int *i, t_token **token,
					t_token **current);
void			append_token(t_token **token, t_token **current, char *value);
void			ft_print_token(t_token *list);

// parser.c
int				check_quotes(char *input);
int				valid_pipe(t_token *list);
int				valid_heredoc(t_token *list);
int				valid_redir_out(t_token *list);
int				valid_redir_in(t_token *list);

// free.c
void			free_token_list(t_token *head);

// environment.c
t_env			*linked_node_env(char **env);
t_env			*create_node_env(char *name, char *content);
void			free_env(t_env *env);
char			*get_env_name(char *env);
char	        *get_env_value(t_env *env, char *name);
void			insert_node(char *env_name, t_env *curr_node, char *content);
void			free_token_list(t_token *head);
void			free_cmd(t_cmd *cmd);

// execution.c
char			**find_path(t_env *env);
char			*join_path_with_cmd(char **path, t_cmd *cmd);
void			execution_cmd(t_env *env, t_cmd *cmd);
char			**recreate_env(t_env *env);
int				count_nodes(t_env *env);

// utils.c
char			*ft_join_three(char *s1, char *s2, char *s3);
#endif
