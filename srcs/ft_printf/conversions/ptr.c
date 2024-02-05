/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:39:36 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/03 15:05:57 by ugdaniel         ###   ########.fr       */
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
		GET_NUMBER_LENGTH(&len, addr, 16);
	else
		len = 3;
	len += 2;
	_ADD_PADDING_SPACES(
	if (addr)
		done += (_ft_printf_out_xX('x', addr, fd, 1, 0, 0, 0));
	else
		done += (write(fd, "(nil)", len));
	);
	return (done);
}
