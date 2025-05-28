# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 20:04:53 by pvitor-l          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2025/05/28 16:47:31 by pvitor-l         ###   ########.fr        #
=======
#    Updated: 2025/05/28 18:17:59 by brunogue         ###   ########.fr        #
>>>>>>> dev
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
<<<<<<< HEAD
FILES = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parse.c
=======
FILES = $(SRC_DIR)/main.c $(SRC_DIR)/free.c

VALGRIND = valgrind --leak-check=full \
	--show-leak-kinds=all \
	--suppressions=supress.supp
>>>>>>> dev

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
	$(VALGRIND) ./$(NAME)

re: fclean all 

.PHONY: all clean fclean re