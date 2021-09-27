# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 12:23:21 by ugdaniel          #+#    #+#              #
#    Updated: 2021/09/27 13:46:47 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRCS		=	$(wildcard srcs/*/*.c)
HEADERS		=	-I srcs/. \
				-I srcs/array \
				-I srcs/char \
				-I srcs/list \
				-I srcs/mem \
				-I srcs/string \
				-I srcs/write

CC			=	@clang
FLAGS		=	-Wall -Wextra -Werror
OBJS		=	$(SRCS:c=o)

_white		= \033[39m
_green		= \033[92m
_magenta	= \033[95m
_yellow		= \033[33m
_blue		= \033[34m
_gray		= \033[37m
_red		= \033[91m
_cyan		= \033[96m

all: $(NAME)
	@printf "\033[2K\r$(_blue)$(NAME) ready!\n$(white)"

$(NAME): text1 $(OBJS)
	@ar rcs $(NAME) $(OBJS)

.c.o:
	@printf "\033[2K\r$(_yellow)$< $(_red)"
	$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< 

clean:
	@rm -f $(OBJS)

fclean: clean
	@printf "$(_magenta)Libft cleaned$(_white)\n"
	@rm -f $(NAME)

re: fclean all

text1:
	@printf "$(gray)Compiling $(NAME)... \t$(_white)\n"

.PHONY: all clean fclean re text1
