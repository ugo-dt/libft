# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 12:23:21 by ugdaniel          #+#    #+#              #
#    Updated: 2024/07/26 13:29:44 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

#@echo "$(foreach src,$(SRCS),$(src)\n)"
SRCS		=	srcs/array/2d_array.c \
				srcs/array/str_array.c \
				srcs/char/ft_isalnum.c \
				srcs/char/ft_isalpha.c \
				srcs/char/ft_isascii.c \
				srcs/char/ft_isdigit.c \
				srcs/char/ft_islower.c \
				srcs/char/ft_isprint.c \
				srcs/char/ft_isspace.c \
				srcs/char/ft_isupper.c \
				srcs/char/ft_tolower.c \
				srcs/char/ft_toupper.c \
				srcs/ft_printf/ft_dprintf.c \
				srcs/ft_printf/ft_printf.c \
				srcs/ft_printf/ft_snprintf.c \
				srcs/ft_printf/internal/_ft_vdprintf.c \
				srcs/ft_printf/internal/_ft_vsnprintf.c \
				srcs/ft_printf/internal/char.c \
				srcs/ft_printf/internal/hex.c \
				srcs/ft_printf/internal/ptr.c \
				srcs/ft_printf/internal/signed.c \
				srcs/ft_printf/internal/string.c \
				srcs/ft_printf/internal/unsigned.c \
				srcs/list/ft_lstadd_back.c \
				srcs/list/ft_lstadd_front.c \
				srcs/list/ft_lstclear.c \
				srcs/list/ft_lstdelone.c \
				srcs/list/ft_lstiter.c \
				srcs/list/ft_lstlast.c \
				srcs/list/ft_lstmap.c \
				srcs/list/ft_lstnew.c \
				srcs/list/ft_lstsize.c \
				srcs/math/ft_abs.c \
				srcs/math/ft_fabs.c \
				srcs/math/ft_fabsf.c \
				srcs/math/ft_fabsl.c \
				srcs/math/ft_labs.c \
				srcs/math/ft_llabs.c \
				srcs/mem/ft_bzero.c \
				srcs/mem/ft_calloc.c \
				srcs/mem/ft_memccpy.c \
				srcs/mem/ft_memchr.c \
				srcs/mem/ft_memcmp.c \
				srcs/mem/ft_memcpy.c \
				srcs/mem/ft_memmove.c \
				srcs/mem/ft_memset.c \
				srcs/string/ft_atoi.c \
				srcs/string/ft_itoa.c \
				srcs/string/ft_len_to_char.c \
				srcs/string/ft_len_to_space.c \
				srcs/string/ft_split.c \
				srcs/string/ft_str_tolower.c \
				srcs/string/ft_str_toupper.c \
				srcs/string/ft_strcat.c \
				srcs/string/ft_strchr.c \
				srcs/string/ft_strcmp.c \
				srcs/string/ft_strcpy.c \
				srcs/string/ft_strdup.c \
				srcs/string/ft_strjoin.c \
				srcs/string/ft_strjoin_3.c \
				srcs/string/ft_strlcat.c \
				srcs/string/ft_strlcpy.c \
				srcs/string/ft_strlen.c \
				srcs/string/ft_strmapi.c \
				srcs/string/ft_strncat.c \
				srcs/string/ft_strncmp.c \
				srcs/string/ft_strncpy.c \
				srcs/string/ft_strndup.c \
				srcs/string/ft_strnlen.c \
				srcs/string/ft_strnstr.c \
				srcs/string/ft_strrchr.c \
				srcs/string/ft_strsplit.c \
				srcs/string/ft_strtrim.c \
				srcs/string/ft_substr.c \
				srcs/write/ft_putchar.c \
				srcs/write/ft_putchar_fd.c \
				srcs/write/ft_putendl.c \
				srcs/write/ft_putendl_fd.c \
				srcs/write/ft_putnbr.c \
				srcs/write/ft_putnbr_fd.c \
				srcs/write/ft_putstr.c \
				srcs/write/ft_putstr_fd.c

OBJS		=	$(SRCS:.c=.o)
INCLUDE		=	-I include

CC			=	clang
C@FLAGS		=	-Wall -Wextra -Werror -pedantic

_default	=	\033[39m
_green		= 	\033[92m
_magenta	= 	\033[95m
_yellow		= 	\033[33m
_blue		= 	\033[34m
_gray		= 	\033[37m
_red		= 	\033[91m
_cyan		= 	\033[96m

ifndef verbose
  SILENT = @
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(SILENT)ar rcs $(NAME) $(OBJS)
	@echo "\033[2K\r$(_green)Successfully built $(NAME)$(_default)"

.c.o:
	@echo "Compiling $<"
	$(SILENT)$(CC) $(C@FLAGS) $(INCLUDE) -o $@ -c $<

clean:
	$(SILENT)rm -f $(OBJS)

fclean: clean
	$(SILENT)rm -f $(NAME)

re: fclean all

test: $(NAME)
	./test/run_tests.sh all

.PHONY: all clean fclean re test
