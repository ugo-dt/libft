# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 12:23:21 by ugdaniel          #+#    #+#              #
#    Updated: 2021/09/23 21:46:32 by ugdaniel         ###   ########.fr        #
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
_gray		= \033[37m
_cyan		= \033[96m
_red		= \033[91m

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "\033[2K\r$(_cyan)Libft compiled\n$(white)"

.c.o:
	@printf "\033[2K\r$(_yellow)Compiling $< $(_red)"
	$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< 

clean:
	@rm -f $(OBJS)

fclean: clean
	@printf "$(_magenta)Libft cleaned$(_white)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
