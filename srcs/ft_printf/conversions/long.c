/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:03:20 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/03 15:06:11 by ugdaniel         ###   ########.fr       */
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

	done = 0;
	GET_NUMBER_LENGTH(&len, nb, 10);
	_ADD_PADDING(flag_zero,
	done += _ft_printf_out_l_internal(nb, fd);
	);
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

	done = 0;
	GET_NUMBER_LENGTH(&len, nb, 10);
	_ADD_PADDING(flag_zero,
	done += _ft_printf_out_ll_internal(nb, fd);
	);
	return (done);
}
