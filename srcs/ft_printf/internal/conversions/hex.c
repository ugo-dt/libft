/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:29:51 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 19:26:49 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

void	_ft_printf_make_hex_string(char *s, char x, unsigned int nb, int alt, int length)
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
}

/** The function _ft_printf_out_xX() writes the number fd in hexadecimal to the
 * file descriptor fd.
 * 
 * @returns The number of characters written. */
int	_ft_printf_out_xX(char x, unsigned int nb, int fd, struct _specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;

	GET_NUMBER_LENGTH(&arg_length, nb, 16);
	if (specs->flags.alt)
		arg_length += 2;
	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
	_ft_printf_make_hex_string(s, x, nb, specs->flags.alt, arg_length);
	write(fd, s, specs->info.width);
	free(s);
	return (specs->info.width);
}
