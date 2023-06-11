#!/bin/bash

current_dir=$(pwd)
underline="\033[4m"
reset="\033[0m"

run_test()
{
	clang -Wall -Wextra -Werror test/$1/main.c -o test/$1/$1.test -I include -I test $0/../libft.a
	printf "$1\n"
	./test/$1/$1.test
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

if [ "$1" == "all" ]; then
	run_all_tests
elif [ -n "$1" ]; then
	run_test "$1"
else
	printf "No test provided.\nSynopsis: $0 ${underline}test${reset}\n\nAvailable tests: \narray\nchar\nft_printf\nlist\nmath\nmem\nstring\nwrite\n"
fi

