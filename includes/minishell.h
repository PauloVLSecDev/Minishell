/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:55:53 by brunogue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/27 17:11:44 by pvitor-l         ###   ########.fr       */
=======
/*   Updated: 2025/05/27 20:31:58 by brunogue         ###   ########.fr       */
>>>>>>> 5480673dd4586a90351f1d538443a5e304ea1a41
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

<<<<<<< HEAD
=======
// ENUM DE TIPOS DE TOKENS
>>>>>>> 5480673dd4586a90351f1d538443a5e304ea1a41
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
<<<<<<< HEAD
    char    **args;
    int input_file;
    int output_file;
    int append_mode;  // yet don't know how this will be aplicated 
    struct  s_cmd *next;
}   t_cmd;
=======
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;
>>>>>>> 5480673dd4586a90351f1d538443a5e304ea1a41

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
int	check_quotes(char *input);

#endif
