/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:56:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 19:45:03 by ugdaniel         ###   ########.fr       */
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

	GET_NUMBER_LENGTH(&len, unsigned long, nb, 10);
	done = 0;
	if (!flag_left)
		done += _add_padding(width, flag_zero ? '0' : ' ', len, fd);
	done += _ft_printf_out_ul_internal(nb, fd);
	if (flag_left)
		done += _add_padding(width, ' ', done, fd);
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

	GET_NUMBER_LENGTH(&len, unsigned long long, nb, 10);
	done = 0;
	if (!flag_left)
		done += _add_padding(width, flag_zero ? '0' : ' ', len, fd);
	done += _ft_printf_out_ull_internal(nb, fd);
	if (flag_left)
		done += _add_padding(width, ' ', done, fd);
	return (done);
}
