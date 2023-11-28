/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:29:51 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/28 20:15:05 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t	_ft_printf_out_c(char c, int fd);

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
		done += _ft_printf_out_c(nb + 48, fd);
	else if (nb < 16)
		done += _ft_printf_out_c(nb + caps, fd);
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
size_t	_ft_printf_out_xX(char x, unsigned int nb, int fd, int alt_form)
{
	size_t done;

	done = 0;
	if (alt_form && nb != 0)
	{
		done += _ft_printf_out_c('0', fd);
		done += _ft_printf_out_c(x, fd);
	}
	done += _ft_printf_out_xX_internal(x, nb, fd);
	return (done);
}
