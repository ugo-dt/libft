#!/bin/bash

current_dir=$(pwd)
underline="\033[4m"
reset="\033[0m"

run_test()
{
	echo "----- $1 -----"
	(
		(clang -Wall -Wextra -Werror -Dlibft_test_use_real=1 $1/main.c -o $1/real -I ../include ../libft.a >/dev/null >&1 \
			&& clang -Wall -Wextra -Werror $1/main.c -o $1/ft -I ../include ../libft.a >/dev/null >&1) \
		|| (printf 'Does not compile. ' && exit 1) \
		&& (diff <(./$1/ft) <(./$1/real) && printf "Diff OK :)\n") || printf "Diff KO :(\n"
	)
	rm ./$1/ft ./$1/real 2> /dev/null
}

run_all_tests()
{
	run_test array
	run_test char
	run_test ft_printf
	run_test list
	run_test math
	run_test mem
	run_test string
	run_test write
}

if [ "$#" -eq 0 ]; then
	printf "Error: no tests provided.\nUsage: $0 ${underline}[TEST|all]${reset}\n\nAvailable tests: \n- array\n- char\n- ft_printf\n- list\n- math\n- mem\n- string\n- write\n"
	exit 1
fi

if [ "$1" == "all" ]; then
	run_all_tests
	exit 0
fi

for test_name in "$@"; do
	run_test "$test_name"
done