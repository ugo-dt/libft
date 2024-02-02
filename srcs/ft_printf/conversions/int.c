/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:23:32 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/12/01 12:02:40 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t	_ft_printf_out_c(char c, int fd);

static size_t _ft__printf_out_di_internal(int nb, int fd)
{
	size_t	done;

	done = 0;
	if (nb == INT_MIN)
	{
		done += _ft__printf_out_di_internal(INT_MIN / 10, fd);
		done += _ft_printf_out_c('8', fd);
	}
	else if (nb < 0)
	{
		done += _ft_printf_out_c('-', fd);
		done += _ft__printf_out_di_internal(-nb, fd);
	}
	else if (nb < 10)
		done += _ft_printf_out_c(nb + 48, fd);
	else
	{
		done += _ft__printf_out_di_internal(nb / 10, fd);
		done += _ft__printf_out_di_internal(nb % 10, fd);
	}
	return (done);
}

/** The function _ft_printf_out_di() writes the number nb to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_di(int nb, int fd, int flag_zero)
{
	(void)flag_zero;
	return _ft__printf_out_di_internal(nb, fd);
}
