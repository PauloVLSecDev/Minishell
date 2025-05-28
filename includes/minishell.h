/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:55:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/05/28 17:37:19 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "../libft/libft.h"
# include "parser.h"
# include "token.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

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
	DOUBLE_QUOTE = '"',
	QUOTE = '\''
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

// FUNÇÕES
int				check_quotes(char *input);
t_token_type	find_token_type(char *str);
t_token			*tokenization(char *input);
void			ft_print_token(t_token *list);
void			free_token_list(t_token *head);

#endif
