/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:52:12 by brunogue          #+#    #+#             */
/*   Updated: 2025/07/07 15:39:15 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_token	t_token;

typedef struct s_cmd	t_cmd;

typedef struct s_env	t_env;

typedef struct s_shell
{
	t_token				*token;
	t_cmd				*cmd;
	t_env				*env;
	char				*input;
	char				**env_copy;
	int					exit_status;
}						t_shell;

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
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd
{
	char				**args;
	int					is_builtin;
	char				*infile;
	char				*outfile;
	int					append_mode;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
}						t_env;

#endif
