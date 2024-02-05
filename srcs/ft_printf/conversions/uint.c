/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:51:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/03 15:06:18 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

static size_t	_ft_printf_out_u_internal(unsigned int nb, int fd)
{
	size_t done;

	done = 0;
	if (nb < 10)
		done += _ft_printf_out_c_internal(nb + 48, fd);
	else
	{
		done += _ft_printf_out_u_internal(nb / 10, fd);
		done += _ft_printf_out_u_internal(nb % 10, fd);
	}
	return (done);
}

/* The function _ft_printf_out_u() writes the unsigned number nb to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_u(unsigned int nb, int fd, int flag_zero, int flag_left, int width)
{
	size_t done, len;

	done = 0;
	GET_NUMBER_LENGTH(&len, nb, 10);
	_ADD_PADDING(flag_zero,
	done += _ft_printf_out_u_internal(nb, fd);
	);
	return (done);
}
