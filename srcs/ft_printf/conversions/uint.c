/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:51:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/12/01 11:59:36 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t	_ft_printf_out_c(char c, int fd);

/* The function _ft_printf_out_u() writes the unsigned number nb to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_u(uint32_t nb, int fd, int flag_zero)
{
	size_t	done;

	done = 0;
	if (nb < 10)
		done += _ft_printf_out_c(nb + 48, fd);
	else
	{
		done += _ft_printf_out_u(nb / 10, fd, flag_zero);
		done += _ft_printf_out_u(nb % 10, fd, flag_zero);
	}
	return (done);
}
