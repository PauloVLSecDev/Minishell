/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:55:53 by brunogue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/27 15:42:11 by brunogue         ###   ########.fr       */
=======
/*   Updated: 2025/05/27 16:06:04 by brunogue         ###   ########.fr       */
>>>>>>> 5c99cd2df882a5a41f7e586fc01784b46c2f9680
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

typedef enum e_token_type
{
    TOKEN_WORD, // anyware word also can be key word for exmple -l, -w, are util for amost comands  
    TOKEN_PIPE, // |
    TOKEN_REDIR_IN, // <
    TOKEN_REDIR_OUT, // >
    TOKEN_APPEND, // << I don't know how this function
	DOUBLE_QUOTE = '"', // we have changed
	QUOTE = '\'', // should also be changed
<<<<<<< HEAD
}	t_token_type;

typedef	struct s_cmd 
{
    char    **args;
    int input_file;
    int output_file;
    int append_mode;  // yet don't know how this will be aplicated 
    struct  s_cmd *next;
}   t_cmd;
=======
};
>>>>>>> 5c99cd2df882a5a41f7e586fc01784b46c2f9680

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
