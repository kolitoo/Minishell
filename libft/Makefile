# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourdon <abourdon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 13:58:40 by lgirault          #+#    #+#              #
#    Updated: 2023/05/04 14:26:25 by abourdon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -rf

GREEN=\033[33;32m
BLUE=\033[0;34m
BOLD=\033[1m
RESET=\033[0m

SRC =		ft_memcpy.c \
	ft_isalpha.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strrchr.c \
	ft_isascii.c \
	ft_memchr.c \
	ft_memset.c \
	ft_strlen.c \
	ft_tolower.c \
	ft_bzero.c \
	ft_isdigit.c \
	ft_memcmp.c \
	ft_strchr.c \
	ft_strncmp.c \
	ft_toupper.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_memcpy.c \
	ft_strlcat.c \
	ft_strnstr.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_itoa.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_split.c \
	ft_putnbr_fd.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_front.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_printf.c \
	ft_putchar_fd_printf.c \
	ft_putnb_base.c \
	ft_putnbr_unsi.c \
	ft_putstr.c \
	ft_putnbr.c \
	ft_putvoid.c \
	ft_strcmp.c \
	get_next_line.c \
	get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 
	
$(NAME): $(OBJ)
	@echo "$(BLUE)$(BOLD)Compiling $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(BLUE)$(BOLD)Cleaning $(NAME)...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re