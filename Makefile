# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 20:04:53 by pvitor-l          #+#    #+#              #
#    Updated: 2025/07/14 17:42:06 by brunogue         ###   ########.fr        #
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
		$(SRC_DIR)/parser/parser.c \
		$(SRC_DIR)/token/token.c \
		$(SRC_DIR)/token/token_utils.c \
		$(SRC_DIR)/built-in/exec_builtin.c \
		$(SRC_DIR)/built-in/pwd.c \
		$(SRC_DIR)/built-in/cd.c \
		$(SRC_DIR)/built-in/echo.c \
		$(SRC_DIR)/built-in/env.c \
		$(SRC_DIR)/built-in/exit.c \
		$(SRC_DIR)/built-in/unset.c \
		$(SRC_DIR)/built-in/export/export.c \
		$(SRC_DIR)/built-in/export/export_utils.c \
		$(SRC_DIR)/built-in/export/valid_export.c \
		$(SRC_DIR)/expand/environment.c \
		$(SRC_DIR)/execution/execution.c \
		$(SRC_DIR)/execution/global_execute.c \
		$(SRC_DIR)/execution/command.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/execution/pipe.c \
		$(SRC_DIR)/execution/smart_execute.c \
		$(SRC_DIR)/redirect/valid_all.c \
		$(SRC_DIR)/redirect/redirect.c \
		$(SRC_DIR)/redirect/redirect_utils.c \
		$(SRC_DIR)/expand/expand.c 

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
