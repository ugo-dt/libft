/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:39:36 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 17:38:13 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t	_ft_printf_out_s(const char *s, int fd);
size_t	_ft_printf_out_xX(char x, unsigned int nb, int fd, int flag_hash, int flag_zero, int flag_left, int width);

/** The function _ft_printf_out_p() writes the address addr in hexadecimal
 * to the file descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_p(size_t addr, int fd)
{
	return (_ft_printf_out_xX('x', addr, fd, 1, 0, 0, 0));
}
