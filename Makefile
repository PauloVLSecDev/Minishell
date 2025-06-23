# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 20:04:53 by pvitor-l          #+#    #+#              #
#    Updated: 2025/06/23 13:41:14 by brunogue         ###   ########.fr        #
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
		$(SRC_DIR)/built-in/pwd.c \
		$(SRC_DIR)/built-in/cd.c \
		$(SRC_DIR)/built-in/echo.c \
		$(SRC_DIR)/built-in/env.c \
		$(SRC_DIR)/built-in/exit.c \
		$(SRC_DIR)/environment.c \
		$(SRC_DIR)/execution.c \
		$(SRC_DIR)/global_execute.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/pipe.c 

VALGRIND = valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	--trace-children=yes \
	--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
	--suppressions=supress.supp

OBJ = $(FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

valgrind:
	-$(VALGRIND) ./$(NAME)

re: fclean all 

.PHONY: all clean fclean re
