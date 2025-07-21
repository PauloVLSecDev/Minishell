/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:55:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/21 19:19:08 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../libft/libft.h"
# include "struct.h"
# include "builtin.h"
// LIBS
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define AVOID_TOKENS " \t\r\v\f\n"
# define SPECIALS_CHARS "|><\"\'"
# define QUOTE '\''
# define DOUBLE_QUOTE '"'

// token.c
t_token_type	find_token_type(char *str);
t_token			*tokenization(t_token *token, char *input, t_token *current);
int				handle_quotes(char *input, int *i, t_token **token,
					t_token **current);
void			append_token(t_token **token, t_token **current, char *value);
void			ft_print_token(t_token *list);
int				extract_redir_or_pipe(char *input, int *i, t_token **token,
					t_token **current);
int				ft_avoid_tokens(char *input, int *i);

// parser.c
int				check_quotes(char *input);
int				valid_pipe(t_token *list);
int				valid_heredoc(t_token *list);
int				valid_redir_out(t_token *list);
int				valid_redir_in(t_token *list);
int				valid_append(t_token *token);

// free.c
void			free_token_list(t_token *head);
void			cleanup_iteration(void);

// environment.c
t_env			*linked_node_env(char **env);
t_env			*create_node_env(char *name, char *content);
void			free_env(t_env *env);
char			*get_env_name(char *env);
char			*get_env_value(t_env *env, char *name);
void			insert_node(char *env_name, t_env *curr_node, char *content);
void			free_token_list(t_token *head);
void			free_cmd(t_cmd *cmd);

// execution.c
char			**find_path(t_env *env);
char			*join_path_with_cmd(char **path, t_cmd *cmd);
char			**recreate_env(t_env *env);
int				count_nodes(t_env *env);

// global_exection.c
void			exec_all(t_cmd *cmd);
void			exec_external(t_cmd *cmd, char **env, char **path);

void			expand_all_args(t_cmd *cmd);

// expand.c
char			*expand_var(char *arg);
char			*expand_env(char *arg, int *i, t_env *env);
char			*which_expand(char c);
char			*append_str(char *dest, const char *src);
int				verify_dollar_sign(char *arg, char **expanded);

// utils.c
char			*ft_join_three(char *s1, char *s2, char *s3);
void			init_shell(t_env *env);
t_shell			*get_shell(void);

// command.c
void			handle_command(t_token *token);
void			process_all(t_cmd **cmd, t_token **token, int *i);
void			process_pipe(t_cmd **cmd, t_token **token, int *i);
void			process_word(t_cmd **cmd, t_token **token, int *i);
t_cmd			*create_cmd_node(t_token *token);

// pipe.c
void			execute_pipeline(t_cmd *cmd);
void			create_child_process(int *pipefd, t_cmd *cmd, int *prev_fd);

// single_command.c
void			smart_execute(t_cmd *cmd);
void			exec_single_command(t_cmd *cmd, char **new_env, char **path);

// redirect.c
int				process_redirect(t_cmd **cmd, t_token **token, char *filename);
int				redir_actions(t_cmd *cmd);
int				valid_file(char *filename, t_cmd **cmd);
void			restaure_for_origin_fds(t_fd_backup *backup);
void			backup_fds(t_fd_backup *backup);
void			close_fds(t_fd_backup *backup);

// valid_all.c
int				valid_metacharacteres(t_token *token);

// SIGNALS.C
void			setup_signals(void);
void			on_sigint(int signum);
void			on_sigquit(int signum);

// HEREDOC.C
void	process_heredoc(t_token *current, int i, t_cmd **cmd);
void			heredoc_manager(t_token *current, int fd_heredoc);
void	exec_heredoc(char *delimiter, int quotes, int fd_heredoc);
void			heredoc(t_token *token);
void			close_all(void);

#endif
