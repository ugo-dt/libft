/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:29:51 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 19:45:15 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

static size_t _ft_printf_out_xX_internal(char x, unsigned int nb, int fd)
{
	size_t	done;
	int		caps;

	if (x == 'X')
		caps = 55; // 'A' means 10; 'A' is 97 in ascii
	else
		caps = 87; // 'a' is 97
	done = 0;
	if (nb < 10)
		done += _ft_printf_out_c_internal(nb + 48, fd);
	else if (nb < 16)
		done += _ft_printf_out_c_internal(nb + caps, fd);
	else
	{
		done += _ft_printf_out_xX_internal(x, nb / 16, fd);
		done += _ft_printf_out_xX_internal(x, nb % 16, fd);
	}
	return (done);
}

/** The function _ft_printf_out_xX() writes the number fd in hexadecimal to the
 * file descriptor fd.
 * 
 * @returns The number of characters written. */
size_t	_ft_printf_out_xX(char x, unsigned int nb, int fd, int flag_hash, int flag_zero, int flag_left, int width)
{
	size_t done, len;

	GET_NUMBER_LENGTH(&len, unsigned int, nb, 16);
	done = 0;
	if (flag_hash && nb != 0)
	{
		done += _ft_printf_out_c_internal('0', fd);
		done += _ft_printf_out_c_internal(x, fd);
	}
	if (!flag_left)
		done += _add_padding(width, flag_zero ? '0' : ' ', len, fd);
	done += _ft_printf_out_xX_internal(x, nb, fd);
	if (flag_left)
		done += _add_padding(width, ' ', done, fd);
	return (done);
}
