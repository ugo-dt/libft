/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:39:36 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 20:10:01 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

/** The function _ft_printf_out_p() writes the address addr in hexadecimal
 * to the file descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_p(size_t addr, int fd, int flag_left, int width)
{
	size_t done, len;

	done = 0;
	if (addr)
	{
		GET_NUMBER_LENGTH(&len, size_t, addr, 16);
		len += 2;
	}
	else
		len = 5;
	if (!flag_left)
		done += _add_padding(width, ' ', len, fd);
	if (addr)
		done += (_ft_printf_out_xX('x', addr, fd, 1, 0, 0, 0));
	else
		done += (write(fd, "(nil)", len));
	if (flag_left)
		done += _add_padding(width, ' ', done, fd);
	return (done);
}
