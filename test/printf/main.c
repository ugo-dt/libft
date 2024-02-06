/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:39:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/06 22:41:56 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

#if defined libft_test_use_real
# include <stdio.h>
# define ft_dprintf dprintf
# define ft_snprintf snprintf
# define ft_printf printf
#else 
#endif

int main(void)
{
	char str[] = "Hello, world!";
	int done = 0;
	char *nul = NULL;

	done += ft_printf("Hello, world!\n");
	done += ft_printf("Testing int: %d\n", 42);
	done += ft_printf("Testing int: %d\n", 2147483647);
	done += ft_printf("Testing int: %d\n", -2147483647);
	done += ft_printf("Testing int: %i\n", -123);
	done += ft_printf("Testing uint: %u\n", 123);
	done += ft_printf("Testing char: %c\n", 'c');
	done += ft_printf("Testing char: %c\n", '-');
	done += ft_printf("Testing int with char: %i\n", 'A');
	done += ft_printf("Testing string: %s\n", "Hello, world!");
	done += ft_printf("Testing string: %s\n", str);
	done += ft_printf("Testing pointer: %p\n", (void *)123); // 0x7b
	done += ft_printf("Testing pointer: %p\n", (void *)456); // 0x1c8
	done += ft_printf("Testing hex: %x\n", 42222); // a4ee
	done += ft_printf("Testing hex: %X\n", 5050); // 13BA
	done += ft_printf("Testing hex: %#X\n", 5050); // 0X13BA
	done += ft_printf("Testing long: %ld\n", 50505050550);
	done += ft_printf("Testing long: %li\n", 50505050550);
	done += ft_printf("Testing long long: %lli\n", 5050505055050505050LL);
	done += ft_printf("Testing long long: %lld\n", -5050505055050505050LL);
	done += ft_printf("Testing ulong: %lu\n", 50505050550);
	done += ft_printf("Testing ullong: %llu\n", 5050505055050505050ULL);
	done += ft_printf("Testing null str: %s\n", nul);
	done += ft_printf("Testing null ptr: %p\n", NULL);

	done += ft_printf("Testing width of 8: %8c\n", 'a');
	done += ft_printf("Testing width of 8: %*c\n", 8, 'a');
	done += ft_printf("Testing flag left: |%-8c|\n", 'a');
	done += ft_printf("Testing width of 8: %8d\n", 42222);
	done += ft_printf("Testing width of 0: %0d\n", 42222);
	done += ft_printf("Testing flag zero: %08d\n", 42222);
	done += ft_printf("Testing flag left: |%-8d|\n", 42222);
	done += ft_printf("Testing width of 8: %8u\n", 42222);
	done += ft_printf("Testing width of 0: %0u\n", 42222);
	done += ft_printf("Testing flag zero: %08u\n", 42222);
	done += ft_printf("Testing flag left: |%-8u|\n", 42222);
	done += ft_printf("Testing width of 20: %20p\n", (void *)424242);
	done += ft_printf("Testing flag left: |%-20p|\n", (void *)424242);
	done += ft_printf("Testing width of 20: %20s\n", "hello");
	done += ft_printf("Testing flag left: |%-20s|\n", "hello");
	done += ft_printf("Testing flag left: |%-20s|\n", nul);
	done += ft_printf("Testing width: |%20p|\n", nul);
	done += ft_printf("Testing flag left: |%-20p|\n", NULL);

	done += ft_printf("Testing precision: |%8.3s|\n", "hello");
	done += ft_printf("Testing precision: |%1.3s|\n", "hello");
	done += ft_printf("Testing precision: |%18.35s|\n", "hello");

	done += ft_printf("Testing precision: |%8.3d|\n", 1234);
	done += ft_printf("Testing precision: |%08.3d|\n", 1234);
	done += ft_printf("Testing precision: |%1.5d|\n", 1234);
	done += ft_printf("Testing precision: |%10.5d|\n", 1234);
	done += ft_printf("Testing precision: |%10.6d|\n", 1234);
	done += ft_printf("Testing precision: |%10.7d|\n", 1234);
	done += ft_printf("Testing precision: |%10.8d|\n", 1234);
	done += ft_printf("Testing precision: |%10.9d|\n", 1234);
	done += ft_printf("Testing precision: |%10.10d|\n", 1234);
	done += ft_printf("Testing precision: |%10.11d|\n", 1234);
	done += ft_printf("Testing precision: |%10.5d|\n", -1234);
	done += ft_printf("Testing precision: |%10.6d|\n", -1234);
	done += ft_printf("Testing precision: |%10.7d|\n", -1234);
	done += ft_printf("Testing precision: |%10.8d|\n", -1234);
	done += ft_printf("Testing precision: |%10.9d|\n", -1234);
	done += ft_printf("Testing precision: |%10.10d|\n", -1234);
	done += ft_printf("Testing precision: |%10.11d|\n", -1234);

	done += ft_printf("Testing precision: |%2.5d|\n", 1234);
	done += ft_printf("Testing precision: |%2.6d|\n", 1234);
	done += ft_printf("Testing precision: |%2.7d|\n", 1234);
	done += ft_printf("Testing precision: |%2.8d|\n", 1234);
	done += ft_printf("Testing precision: |%2.9d|\n", 1234);
	done += ft_printf("Testing precision: |%2.2d|\n", 1234);
	done += ft_printf("Testing precision: |%2.11d|\n", 1234);
	done += ft_printf("Testing precision: |%2.5d|\n", -1234);
	done += ft_printf("Testing precision: |%2.6d|\n", -1234);
	done += ft_printf("Testing precision: |%2.7d|\n", -1234);
	done += ft_printf("Testing precision: |%2.8d|\n", -1234);
	done += ft_printf("Testing precision: |%2.9d|\n", -1234);
	done += ft_printf("Testing precision: |%2.2d|\n", -1234);
	done += ft_printf("Testing precision: |%2.11d|\n", -1234);

	done += ft_printf("Testing precision: |%8u|\n", 1234);
	done += ft_printf("Testing precision: |%1.5u|\n", 1234);
	done += ft_printf("Testing precision: |%10.5u|\n", 1234);
	done += ft_printf("Testing precision: |%10.6u|\n", 1234);
	done += ft_printf("Testing precision: |%10.7u|\n", 1234);
	done += ft_printf("Testing precision: |%10.8u|\n", 1234);
	done += ft_printf("Testing precision: |%10.9u|\n", 1234);
	done += ft_printf("Testing precision: |%10.10u|\n", 1234);
	done += ft_printf("Testing precision: |%10.11u|\n", 1234);
	done += ft_printf("Testing precision: |%2.5u|\n", 1234);
	done += ft_printf("Testing precision: |%2.6u|\n", 1234);
	done += ft_printf("Testing precision: |%2.7u|\n", 1234);
	done += ft_printf("Testing precision: |%2.8u|\n", 1234);
	done += ft_printf("Testing precision: |%2.9u|\n", 1234);
	done += ft_printf("Testing precision: |%2.2u|\n", 1234);
	done += ft_printf("Testing precision: |%2.11u|\n", 1234);
	done += ft_printf("Testing precision: |%8x|\n", 1234);
	done += ft_printf("Testing precision: |%1.5x|\n", 1234);
	done += ft_printf("Testing precision: |%10.5x|\n", 1234);
	done += ft_printf("Testing precision: |%10.6x|\n", 1234);
	done += ft_printf("Testing precision: |%10.7x|\n", 1234);
	done += ft_printf("Testing precision: |%10.8x|\n", 1234);
	done += ft_printf("Testing precision: |%10.9x|\n", 1234);
	done += ft_printf("Testing precision: |%10.10x|\n", 1234);
	done += ft_printf("Testing precision: |%10.11x|\n", 1234);
	done += ft_printf("Testing precision: |%2.5x|\n", 1234);
	done += ft_printf("Testing precision: |%2.6x|\n", 1234);
	done += ft_printf("Testing precision: |%2.7x|\n", 1234);
	done += ft_printf("Testing precision: |%2.8x|\n", 1234);
	done += ft_printf("Testing precision: |%2.9x|\n", 1234);
	done += ft_printf("Testing precision: |%2.2x|\n", 1234);
	done += ft_printf("Testing precision: |%2.11x|\n", 1234);
	
	done += ft_printf("Testing multiple: %d %i test %u %c test %s %p eeeee %x hello %X\n", 42, -123, 456, 65, "Testing", (void *)999, 64, 100);
	ft_printf("written: %d\n", done);

	char	test[20];
	ft_snprintf(test, 12, "hello, %s", "world");
	ft_printf("|%s|\n", test);
	ft_printf("------------------------\n");
	return (0);
}