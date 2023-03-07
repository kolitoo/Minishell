# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 12:41:59 by abourdon          #+#    #+#              #
#    Updated: 2023/03/07 12:42:42 by abourdon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LIBFT_PATH = ./libft/
LIBFT = libft/libft.a
RM = rm -rf

YELLOW=\033[0;33m
BLUE=\033[0;34m
BOLD=\033[1m
RESET=\033[0m

SRC = 

OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJ) $(LIBFT) include/pipex.h
	@echo "$(BLUE)$(BOLD)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(YELLOW)$(BOLD)$(NAME) compiled!$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_PATH)

	
all: $(NAME)

clean:
	@echo "$(BLUE)$(BOLD)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "$(BLUE)$(BOLD)Cleaning $(NAME)...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: init all clean fclean re