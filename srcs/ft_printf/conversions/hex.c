/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:29:51 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/03 19:54:23 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

/** The function _ft_printf_out_xX() writes the number fd in hexadecimal to the
 * file descriptor fd.
 * 
 * @returns The number of characters written. */
size_t	_ft_printf_out_xX(char x, unsigned int nb, int fd, int flag_hash, int flag_zero, int flag_left, int width)
{
	char *s;
	int	arg_length, caps;
	size_t full_length;

	GET_NUMBER_LENGTH(&arg_length, nb, 16);
	if (flag_hash)
		arg_length += 2;
	if (width < arg_length)
		width = arg_length;
	full_length = width;
	if (x == 'X')
		caps = 55; // 'A' means 10; 'A' is 97 in ascii
	else
		caps = 87; // 'a' is 97
	
	CREATE_STRING(s, full_length, width - arg_length, flag_left, flag_zero,
	if (flag_hash)
	{
		APPEND_CHAR('0', 1);
		APPEND_CHAR(x, 1);
	}
	size_t i = full_length - 1;
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
	);
	write(fd, s, full_length);
	free(s);
	return (full_length);
}
