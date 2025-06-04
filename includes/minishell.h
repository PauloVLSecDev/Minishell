/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:55:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/06/04 17:25:42 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../libft/libft.h"
# include "parser.h"
# include "token.h"

//LIBS
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

#define AVOID_TOKENS " \t\r\v\f"
#define DOUBLE_QUOTE '"'
#define QUOTE '\''

// ENUM DE TIPOS DE TOKENS
typedef enum e_token_type
{
	UNKNOWN = -1,
	TOKEN_WORD,       // Qualquer palavra (pode ser argumento como -l, -w etc.)
	TOKEN_PIPE,       // |
	TOKEN_REDIR_IN,   // <
	TOKEN_REDIR_OUT,  // >
	TOKEN_APPEND,     // >> (não <<) — redirecionamento em modo append
	TOKEN_HEREDOC,    // << — heredoc
	TOKEN_EOF,
}	t_token_type;

// STRUCT DO TOKEN
typedef struct s_token
{
    t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// STRUCT DE COMANDO
typedef struct s_cmd
{
	char			**args;
	int				input_file;
	int				output_file;
	int				append_mode; // 1 se for modo append (>>), 0 se for >
	struct s_cmd	*next;
}	t_cmd;

//token.c
t_token_type	find_token_type(char *str);
t_token *tokenization(t_token *token, char *input);
int     handle_quotes(char *input, int *i, t_token **token, t_token **current);
void    append_token(t_token **token, t_token **current, char *value);
void			ft_print_token(t_token *list);

//parser.c
int				check_quotes(char *input);
int				valid_pipe(t_token *list);

//free.c
void			free_token_list(t_token *head);


#endif