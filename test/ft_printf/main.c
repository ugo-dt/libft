/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:39:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/27 20:28:52 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

#if defined libft_test_use_real
# include <stdio.h>
# define ft_printf printf
#endif

int main(void)
{
	char str[] = "Hello, world!";
	char *nullstr = NULL;
	int done = 0;

	done += ft_printf("Hello, world!");
	done += ft_printf("Testing int: %d\n", 42);
	done += ft_printf("Testing int: %i\n", -123);
	done += ft_printf("Testing uint: %u\n", 123);
	done += ft_printf("Testing char: %i\n", 'A');
	done += ft_printf("Testing char: %c\n", 'r');
	done += ft_printf("Testing string: %s\n", "Hello, world!");
	done += ft_printf("Testing string: %s\n", str);
	done += ft_printf("Testing pointer: %p\n", (void *)123);
	done += ft_printf("Testing pointer: %p\n", (void *)456);
	done += ft_printf("Testing hex: %x\n", 42222);
	done += ft_printf("Testing hex: %X\n", 5050);
	ft_printf("written: %d\n", done);
	done += ft_printf("Testing null string: %p\n", nullstr);
	return (0);
}