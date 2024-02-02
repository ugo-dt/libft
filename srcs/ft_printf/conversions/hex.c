/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:29:51 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 17:42:16 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t	_ft_printf_out_c(char c, int fd);

static size_t _ft__printf_out_xX_internal(char x, unsigned int nb, int fd)
{
	size_t	done;
	int		caps;

	if (x == 'X')
		caps = 55; // 'A' means 10; 'A' is 97 in ascii
	else
		caps = 87; // 'a' is 97
	done = 0;
	if (nb < 10)
		done += _ft_printf_out_c(nb + 48, fd);
	else if (nb < 16)
		done += _ft_printf_out_c(nb + caps, fd);
	else
	{
		done += _ft__printf_out_xX_internal(x, nb / 16, fd);
		done += _ft__printf_out_xX_internal(x, nb % 16, fd);
	}
	return (done);
}

static size_t	_get_hex_number_length(unsigned int nb)
{
	size_t len;
	unsigned int tmp;

	tmp = nb;
	len = 1;
	while (tmp > 16)
	{
		tmp /= 16;
		len++;
	}
	return (len);
}

/** The function _ft_printf_out_xX() writes the number fd in hexadecimal to the
 * file descriptor fd.
 * 
 * @returns The number of characters written. */
size_t	_ft_printf_out_xX(char x, unsigned int nb, int fd, int flag_hash, int flag_zero, int flag_left, int width)
{
	size_t done;
	int padding;

	done = 0;
	if (flag_hash && nb != 0)
	{
		done += _ft_printf_out_c('0', fd);
		done += _ft_printf_out_c(x, fd);
	}
	padding = width - _get_hex_number_length(nb) - done;
	if (width > 0 && !flag_left)
		while (padding-- > 0)
			done += _ft_printf_out_c(flag_zero ? '0' : ' ', fd);
	done += _ft__printf_out_xX_internal(x, nb, fd);
	if (width > 0 && flag_left)
		while (padding-- > 0)
			done += _ft_printf_out_c(' ', fd);
	return (done);
}
