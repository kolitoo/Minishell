# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 12:41:59 by abourdon          #+#    #+#              #
#    Updated: 2023/05/10 19:32:13 by lgirault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_PATH = ./libft/
LIBFT = libft/libft.a
RM = rm -rf

GREEN=\033[33;32m
BLUE=\033[0;34m
BOLD=\033[1m
RESET=\033[0m

	
SRC = src/minishell.c \
	src/parsing/space.c \
	src/parsing/create_env.c \
	src/parsing/parsing.c \
	src/parsing/split_incurve.c \
	src/parsing/split_incurve3.c \
	src/parsing/utils_chevron.c \
	src/parsing/utils_cote.c \
	src/parsing/utils_cote2.c \
	src/parsing/file.c \
	src/parsing/pipe.c \
	src/parsing/env_utils.c \
	src/parsing/env_utils2.c \
	src/utils/free.c \
	src/utils/free2.c \
	src/utils/lst_fonction.c \
	src/utils/malloc.c \
	src/utils/utils.c \
	src/utils/signal.c \
	src/utils/ft_split2.c \
	src/execex/no_pipe.c \
	src/execex/close_file.c \
	src/builtin/check_builtin.c \
	src/builtin/echo_builtin.c \
	src/builtin/echo_builtin2.c \
	src/builtin/cd_builtin.c \
	src/builtin/pwd_builtin.c \
	src/builtin/export_builtin.c \
	src/builtin/unset_builtin.c \
	src/builtin/env_builtin.c \
	src/builtin/exit_builtin.c \
	src/builtin/exit_builtin2.c \
	src/builtin/export_builtin2.c \
	src/builtin/export_builtin3.c \
	src/builtin/export_builtin4.c \
	src/pipex/pipex.c \
	src/pipex/find_good_path.c \
	src/pipex/free_pipex.c \
	src/pipex/here_doc.c \
	src/pipex/here_doc2.c \
	src/pipex/make_tab_path.c \
	src/pipex/utils.c \
	src/pipex/utils2.c \
	src/pipex/child.c \
	src/pipex/open_outfile.c \
	src/pipex/open_infile.c \
	src/pipex/error_managment.c \

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
	@make fclean --no-print-directory -C $(LIBFT_PATH)

re: fclean all

.PHONY: init all clean fclean re