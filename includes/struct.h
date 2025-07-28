/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:52:12 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/28 17:52:06 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "builtin.h"
# include "minishell.h"

typedef struct s_token		t_token;

typedef struct s_cmd		t_cmd;

typedef struct s_env		t_env;

typedef struct s_fd_backup	t_fd_backup;

typedef struct s_shell
{
	t_token					*token;
	t_cmd					*cmd;
	t_env					*env;
	t_fd_backup				*backup_fds;
	char					*input;
	int						must_execute;
	int						heredoc_counter;
	char					**env_copy;
	int						exit_status;
}							t_shell;

typedef struct s_fd_backup
{
	int						std_infile;
	int						std_outfile;
	int						std_err;
}							t_fd_backup;

typedef enum e_token_type
{
	UNKNOWN = -1,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
}							t_token_type;

typedef enum e_quotemode
{
	QUOTE_NONE = 0,
	QUOTE_SINGLE = 1,
	QUOTE_DOUBLE = 2
}							t_qmode;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*next;
}							t_token;

typedef struct s_heredoc
{
	char					*filename;
	struct s_token			*next;
}							t_heredoc;

typedef struct s_cmd
{
	char					**args;
	int						is_builtin;
	char					*infile;
	char					*outfile;
	int						append_mode;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_env
{
	char					*name;
	char					*content;
	struct s_env			*next;
}							t_env;

#endif
