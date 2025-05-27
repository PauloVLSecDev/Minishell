/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:55:53 by brunogue          #+#    #+#             */
/*   Updated: 2025/05/27 16:06:04 by brunogue         ###   ########.fr       */
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

typedef struct s_token
{
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

enum e_token_type
{
	UNKNOWN = -1,
    TOKEN_WORD, // anyware word also can be key word for exmple -l, -w, are util for amost comands  
    TOKEN_PIPE, // |
    TOKEN_REDIR_IN, // <
    TOKEN_REDIR_OUT, // >
    TOKEN_APPEND, // << I don't know how this function
	DOUBLE_QUOTE = '"', // we have changed
	QUOTE = '\'', // should also be changed
};

typedef	struct s_cmd 
{
    char    **args;
    int input_file;
    int output_file;
    int append_mode;  // yet don't know how this will be aplicated 
    struct  s_cmd *next;
}   t_cmd;

int		check_quotes(char *imput);

#endif
