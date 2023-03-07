# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 12:41:59 by abourdon          #+#    #+#              #
#    Updated: 2023/03/07 16:32:04 by lgirault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LIBFT_PATH = ./libft/
LIBFT = libft/libft.a
RM = rm -rf

GREEN=\033[33;32m
BLUE=\033[0;34m
BOLD=\033[1m
RESET=\033[0m

SRC = src/minishell.c \
	src/parsing/space.c \
	src/parsing/parsing.c \

OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJ) $(LIBFT) include/minishell.h
	@echo "$(BLUE)$(BOLD)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)$(BOLD)$(NAME) compiled!$(RESET)"

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH)

	
all: $(NAME)

clean:
	@echo "$(BLUE)$(BOLD)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ)
	@make clean --no-print-directory -C $(LIBFT_PATH)

fclean: clean
	@echo "$(BLUE)$(BOLD)Cleaning $(NAME)...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: init all clean fclean re