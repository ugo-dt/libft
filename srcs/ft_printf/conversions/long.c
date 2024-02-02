/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:03:20 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 19:45:11 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

static size_t	_ft_printf_out_l_internal(long long nb, int fd)
{
	size_t done;

	done = 0;
	if (nb <= -9223372036854775807)
	{
		done += _ft_printf_out_l_internal(-922337203685477580, fd);
		done += _ft_printf_out_c_internal(ft_abs((int)(nb % 10)) + 48, fd);
	}
	else if (nb < 0)
	{
		done += _ft_printf_out_c_internal('-', fd);
		done += _ft_printf_out_l_internal(-nb, fd);
	}
	else if (nb < 10)
		done += _ft_printf_out_c_internal(nb + 48, fd);
	else
	{
		done += _ft_printf_out_l_internal(nb / 10, fd);
		done += _ft_printf_out_l_internal(nb % 10, fd);
	}
	return (done);
}

/** The function _ft_printf_out_l() writes the long number nb to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_l(long nb, int fd, int flag_zero, int flag_left, int width)
{
	size_t done, len;

	GET_NUMBER_LENGTH(&len, long, nb, 10);
	done = 0;
	if (!flag_left)
		done += _add_padding(width, flag_zero ? '0' : ' ', len, fd);
	done += _ft_printf_out_l_internal(nb, fd);
	if (flag_left)
		done += _add_padding(width, ' ', done, fd);
	return (done);
}

static size_t	_ft_printf_out_ll_internal(long long nb, int fd)
{
	size_t done;

	done = 0;
	if (nb <= -9223372036854775807)
	{
		done += _ft_printf_out_ll_internal(-922337203685477580, fd);
		done += _ft_printf_out_c_internal(ft_abs((int)(nb % 10)) + 48, fd);
	}
	else if (nb < 0)
	{
		done += _ft_printf_out_c_internal('-', fd);
		done += _ft_printf_out_ll_internal(-nb, fd);
	}
	else if (nb < 10)
		done += _ft_printf_out_c_internal(nb + 48, fd);
	else
	{
		done += _ft_printf_out_ll_internal(nb / 10, fd);
		done += _ft_printf_out_ll_internal(nb % 10, fd);
	}
	return (done);
}

size_t	_ft_printf_out_ll(long long nb, int fd, int flag_zero, int flag_left, int width)
{
	size_t done, len;

	GET_NUMBER_LENGTH(&len, long long, nb, 10);
	done = 0;
	if (!flag_left)
		done += _add_padding(width, flag_zero ? '0' : ' ', len, fd);
	done += _ft_printf_out_ll_internal(nb, fd);
	if (flag_left)
		done += _add_padding(width, ' ', done, fd);
	return (done);
}
