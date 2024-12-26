#!/bin/bash

verbose=false

# Assuming this script is in libft/test
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

underline="\033[4m"
reset="\033[0m"
_default="\033[39m"
_green="\033[92m"
_magenta="\033[95m"
_yellow="\033[33m"
_blue="\033[34m"
_gray="\033[37m"
_red="\033[91m"
_cyan="\033[96m"

log()
{
	if [ "$verbose" = true ]
	then
		printf "$_yellow"
		printf "$1"
		printf "$_default"
	fi
}

_compile_ft()
{
	if [ "$verbose" = true ]
	then
		gcc -Wall -Wextra -Werror -fsanitize=address $SCRIPT_DIR/$1/main.c -o $SCRIPT_DIR/$1/ft -I $SCRIPT_DIR/../include/libft $SCRIPT_DIR/../libft.a
	else
		gcc -Wall -Wextra -Werror -fsanitize=address $SCRIPT_DIR/$1/main.c -o $SCRIPT_DIR/$1/ft -I $SCRIPT_DIR/../include/libft $SCRIPT_DIR/../libft.a >/dev/null 2>&1
	fi
}

_compile_real()
{
	if [ "$verbose" = true ]
	then
		gcc -Wall -Wextra -Werror -fsanitize=address -Dlibft_test_use_real=1 $SCRIPT_DIR/$1/main.c -o $SCRIPT_DIR/$1/real -I $SCRIPT_DIR/../include/libft $SCRIPT_DIR/../libft.a
	else
		gcc -Wall -Wextra -Werror -fsanitize=address -Dlibft_test_use_real=1 $SCRIPT_DIR/$1/main.c -o $SCRIPT_DIR/$1/real -I $SCRIPT_DIR/../include/libft $SCRIPT_DIR/../libft.a >/dev/null 2>&1
	fi
}

_compile()
{
	_compile_real $1 || (_print_color 'Error: original version does not compile.\nMake sure the tests are valid.\n' $_yellow && exit 1)
	_compile_ft $1 || (_print_color 'Does not compile.\nDiff KO\n' $_red && exit 1)
}

_print_color()
{
	printf "$2"
	printf "$1"
	printf "$_default"
}

_run()
{
	if [ "$verbose" = true ]; then
		(diff <($SCRIPT_DIR/$1/ft | tee /dev/tty) <($SCRIPT_DIR/$1/real | tee /dev/tty) && _print_color "Diff OK\n" $_green) || _print_color "Diff KO\n" $_red
	else
		(diff <($SCRIPT_DIR/$1/ft) <($SCRIPT_DIR/$1/real) && _print_color "Diff OK\n" $_green) || _print_color "Diff KO\n" $_red
    fi
}

run_test()
{
    echo "----- $1 -----"
    (
		_compile $1 && _run $1
    )
    rm -f $SCRIPT_DIR/$1/ft $SCRIPT_DIR/$1/real
}

run_all_tests()
{
    run_test array
    run_test char
    run_test printf
    run_test list
    run_test math
    run_test mem
    run_test string
    run_test write
}

show_help()
{
	printf "Usage: $0 ${underline}[TEST|all]${reset} [-v|--verbose]\n\nAvailable tests: \n- array\n- char\n- printf\n- list\n- math\n- mem\n- string\n- write\n"
}

if [ "$#" -eq 0 ]; then
	printf "Error: no tests provided.\nUsage: $0 ${underline}[TEST|all]${reset} [-v|--verbose]\n\nAvailable tests: \n- array\n- char\n- printf\n- list\n- math\n- mem\n- string\n- write\n"
	exit 1
fi

for var in "$@"
do
	case $var in
		-v|--verbose)
			verbose=true
			shift
			;;
		-h|--help)
			show_help
			break
			;;
		all)
			run_all_tests
			;;
		array|char|printf|list|math|mem|string|write)
			run_test "$var"
			;;
		*)
			_print_color "$var: Unknown test\n" $_yellow
			;;
	esac
done