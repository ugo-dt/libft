/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:56:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/03 15:06:28 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

static size_t	_ft_printf_out_ul_internal(unsigned long nb, int fd)
{
	size_t	done;

	done = 0;
	if (nb < 10)
		done += _ft_printf_out_c_internal(nb + 48, fd);
	else
	{
		done += _ft_printf_out_ul_internal(nb / 10, fd);
		done += _ft_printf_out_ul_internal(nb % 10, fd);
	}
	return (done);
}

size_t	_ft_printf_out_ul(unsigned long nb, int fd, int flag_zero, int flag_left, int width)
{
	size_t	done, len;

	done = 0;
	GET_NUMBER_LENGTH(&len, nb, 10);
	_ADD_PADDING(flag_zero,
	done += _ft_printf_out_ul_internal(nb, fd);
	);
	return (done);
}

static size_t	_ft_printf_out_ull_internal(unsigned long long nb, int fd)
{
	size_t done;

	done = 0;
	if (nb < 10)
		done += _ft_printf_out_c_internal(nb + 48, fd);
	else
	{
		done += _ft_printf_out_ull_internal(nb / 10, fd);
		done += _ft_printf_out_ull_internal(nb % 10, fd);
	}
	return (done);
}

size_t	_ft_printf_out_ull(unsigned long long nb, int fd, int flag_zero, int flag_left, int width)
{
	size_t done, len;

	done = 0;
	GET_NUMBER_LENGTH(&len, nb, 10);
	_ADD_PADDING(flag_zero,
	done += _ft_printf_out_ull_internal(nb, fd);
	);
	return (done);
}
