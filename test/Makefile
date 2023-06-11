# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 13:21:22 by ugdaniel          #+#    #+#              #
#    Updated: 2023/02/22 13:25:05 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft_test

SRCS	= srcs/array/main.c
OBJS	= $(SRCS:.c=.o)
INCLUDE	= -I include -I test

CC		=	clang
FLAGS	=	-Wall -Wextra -Werror

white	=	\033[39m
green	= 	\033[92m
magenta	= 	\033[95m
yellow	= 	\033[33m
blue	= 	\033[34m
gray	= 	\033[37m
red		= 	\033[91m
cyan	= 	\033[96m

all:

.c.o:
	@printf "\033[2K\r$(yellow)$< $(_red)"
	@$(CC) $(FLAGS) $(INCLUDE) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@printf "$(magenta)Removed object files$(white)\n"

fclean: clean
	@test -f $(NAME) && rm -f $(NAME) || true
	@printf "$(red)Cleaned $(NAME)$(white)\n"

re: fclean all

text1:
	@printf "$(cyan)Compiling $(NAME)... \t$(white)\n"

test:
	@bash ./test/run_tests.sh

.PHONY: all clean fclean re text1 test
