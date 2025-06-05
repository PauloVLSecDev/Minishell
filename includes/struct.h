/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:52:12 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/05 14:53:48 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "minishell.h"

// ENUM DE TIPOS DE TOKENS
typedef enum e_token_type
{
	UNKNOWN = -1,
	TOKEN_WORD,      // Qualquer palavra (pode ser argumento como -l, -w etc.)
	TOKEN_PIPE,      // |
	TOKEN_REDIR_IN,  // <
	TOKEN_REDIR_OUT, // >
	TOKEN_APPEND,    // >> (não <<) — redirecionamento em modo append
	TOKEN_HEREDOC,   // << — hered
	TOKEN_EOF,
}					t_token_type;

// STRUCT DO TOKEN
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

// STRUCT DE COMANDO
typedef struct s_cmd
{
	char			**args;
	int				is_builtin;
	int				input_file;
	int				output_file;
	int 			append_mode; // 1 se for modo append (>>), 0 se for >
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

#endif