/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:23:32 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 20:01:31 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

static size_t _ft_printf_out_di_internal(int nb, int fd)
{
	size_t	done;

	done = 0;
	if (nb == INT_MIN)
	{
		done += _ft_printf_out_di_internal(INT_MIN / 10, fd);
		done += _ft_printf_out_c_internal('8', fd);
	}
	else if (nb < 0)
	{
		done += _ft_printf_out_c_internal('-', fd);
		done += _ft_printf_out_di_internal(-nb, fd);
	}
	else if (nb < 10)
		done += _ft_printf_out_c_internal(nb + 48, fd);
	else
	{
		done += _ft_printf_out_di_internal(nb / 10, fd);
		done += _ft_printf_out_di_internal(nb % 10, fd);
	}
	return (done);
}

#include <stdio.h>

/** The function _ft_printf_out_di() writes the number nb to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_di(int nb, int fd, int flag_zero, int flag_left, int width)
{
	size_t done, len;

	GET_NUMBER_LENGTH(&len, int, nb, 10);
	done = 0;
	if (!flag_left)
		done += _add_padding(width, flag_zero ? '0' : ' ', len, fd);
	done += _ft_printf_out_di_internal(nb, fd);
	if (flag_left)
		done += _add_padding(width, ' ', done, fd);
	return (done);
}
