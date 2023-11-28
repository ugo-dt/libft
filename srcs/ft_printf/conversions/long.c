/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:03:20 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/28 20:08:54 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t	_ft_printf_out_c(char c, int fd);

/** The function _ft_printf_out_l() writes the long number nb to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_l(long nb, int fd)
{
	size_t	done;

	done = 0;
	if (nb <= -9223372036854775807)
	{
		done += _ft_printf_out_l(-922337203685477580, fd);
		done += _ft_printf_out_c(ft_abs((int)(nb % 10)) + 48, fd);
	}
	else if (nb < 0)
	{
		done += _ft_printf_out_c('-', fd);
		done += _ft_printf_out_l(-nb, fd);
	}
	else if (nb < 10)
		done += _ft_printf_out_c(nb + 48, fd);
	else
	{
		done += _ft_printf_out_l(nb / 10, fd);
		done += _ft_printf_out_l(nb % 10, fd);
	}
	return (done);
}

size_t	_ft_printf_out_ll(long long nb, int fd)
{
	size_t	done;

	done = 0;
	if (nb <= -9223372036854775807)
	{
		done += _ft_printf_out_ll(-922337203685477580, fd);
		done += _ft_printf_out_c(ft_abs((int)(nb % 10)) + 48, fd);
	}
	else if (nb < 0)
	{
		done += _ft_printf_out_c('-', fd);
		done += _ft_printf_out_ll(-nb, fd);
	}
	else if (nb < 10)
		done += _ft_printf_out_c(nb + 48, fd);
	else
	{
		done += _ft_printf_out_ll(nb / 10, fd);
		done += _ft_printf_out_ll(nb % 10, fd);
	}
	return (done);
}
