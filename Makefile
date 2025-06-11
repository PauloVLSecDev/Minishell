# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 20:04:53 by pvitor-l          #+#    #+#              #
#    Updated: 2025/06/11 12:48:37 by brunogue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = srcs
OBJ_DIR = obj
INCLUDES_DIR = includes
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(INCLUDES_DIR)
FILES = $(SRC_DIR)/main.c \
		$(SRC_DIR)/free.c \
		$(SRC_DIR)/parser.c \
		$(SRC_DIR)/token.c \
		$(SRC_DIR)/built-in/exec_builtin.c \
		$(SRC_DIR)/built-in/echo.c \
		$(SRC_DIR)/built-in/pwd.c \
		$(SRC_DIR)/built-in/cd.c \
		$(SRC_DIR)/environment.c \
		$(SRC_DIR)/execution.c \
		$(SRC_DIR)/utils.c 

VALGRIND = valgrind --leak-check=full \
	--show-leak-kinds=all \
	--suppressions=supress.supp

OBJ = $(FILES:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME) $(INCLUDES)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

valgrind:
	-$(VALGRIND) ./$(NAME)

re: fclean all 

.PHONY: all clean fclean re
