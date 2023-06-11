#!/bin/bash

run_test()
{
	clang -Wall -Wextra -Werror test/srcs/$1/*.c -o test/srcs/$1/$1.test -I include -I test libft.a
	printf "$1\n"
	./test/srcs/$1/$1.test
}

run_test array
# run_test char
# run_test ft_printf
# run_test list
# run_test math
# run_test mem
# run_test string
# run_test write
