# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 20:04:53 by pvitor-l          #+#    #+#              #
#    Updated: 2025/05/22 17:31:54 by pvitor-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR)
FLAGS = cc -Wall -Wextra -Werror -g3 
LIBFT = libft 
DIR = src
DIR_OBJ = obj

FILES_PARSE = $DIR/main.c 

obj = $(FILE:.c=.o)

all:

clean: 

%.c=%.o:

fclean: 

re: all

DEGUB:
