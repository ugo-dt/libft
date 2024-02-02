/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:39:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 17:40:17 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

#if defined libft_test_use_real
# include <stdio.h>
# define ft_printf printf
#else 
#endif

int main(void)
{
	char str[] = "Hello, world!";
	int done = 0;

	done += ft_printf("Hello, world!\n");
	done += ft_printf("Testing int: %d\n", 42);
	done += ft_printf("Testing int: %i\n", -123);
	done += ft_printf("Testing uint: %u\n", 123);
	done += ft_printf("Testing char: %i\n", 'A');
	done += ft_printf("Testing char: %c\n", 'r');
	done += ft_printf("Testing string: %s\n", "Hello, world!");
	done += ft_printf("Testing string: %s\n", str);
	done += ft_printf("Testing pointer: %p\n", (void *)123); // 0x7b
	done += ft_printf("Testing pointer: %p\n", (void *)456); // 0x1c8
	done += ft_printf("Testing hex: %x\n", 42222); // a4ee
	done += ft_printf("Testing hex: %X\n", 5050); // 13BA
	done += ft_printf("Testing hex flag hash: %#x\n", 0);
	done += ft_printf("Testing hex width of 8: %8x\n", 42222); // a4ee
	done += ft_printf("Testing hex width of 0: %0x\n", 42222); // a4ee
	done += ft_printf("Testing hex flag zero: %08x\n", 42222); // a4ee
	done += ft_printf("Testing hex flag left: |%-8x|\n", 42222); // a4ee
	done += ft_printf("Testing hex flag left: |%#-8x|\n", 42222); // a4ee
	done += ft_printf("Testing hex: %#X\n", 5050); // 0X13BA
	done += ft_printf("Testing long: %ld\n", 50505050550);
	done += ft_printf("Testing long: %li\n", 50505050550);
	done += ft_printf("Testing long long: %lli\n", 5050505055050505050LL);
	done += ft_printf("Testing long long: %lld\n", -5050505055050505050LL);
	done += ft_printf("Testing ulong: %lu\n", 50505050550);
	done += ft_printf("Testing ullong: %llu\n", 5050505055050505050ULL);
	
	ft_printf("Testing multiple: %d %i %u %c %s %p %x %X\n", 42, -123, 456, 65, "Testing", (void *)999, 64, 100);
	ft_printf("written: %d\n", done);
	// done += ft_printf("Testing null string: %p\n", NULL);
	return (0);
}