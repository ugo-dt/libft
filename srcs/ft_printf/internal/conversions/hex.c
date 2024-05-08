/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:29:51 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/08 17:13:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_conversions.h"

void	_ft_printf_create_hex_internal(char *s, char x, unsigned int nb, int alt, int length)
{
	int caps = x == 'X' ? 55 : 87; // 'A' means 10; 'A' is 97 in ascii, 'a' is 97

	if (alt)
	{
		s[0] = '0';
		s[1] = x;
	}
	int i = length - 1;
	while (nb > 0)
	{
		int digit = nb % 16;
        if (digit < 10)
			s[i] = digit + 48;
		else
			s[i] = digit + caps;
		i--;
		nb /= 16;
	}
	while (i >= (alt ? 2 : 0))
		s[i--] = '0';
}

/** The function _ft_printf_create_xX() writes the number fd in hexadecimal to the
 * file descriptor fd.
 * 
 * @returns The number of characters written. */
char	*_ft_printf_create_xX(char x, unsigned int nb, struct _specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;

	GET_NUMBER_LENGTH(&arg_length, nb, 16, specs->info.precision, int);
	if (specs->flags.alt)
		arg_length += 2;
	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
	_ft_printf_create_hex_internal(s + arg_start, x, nb, specs->flags.alt, arg_length);
	return (s);
}
