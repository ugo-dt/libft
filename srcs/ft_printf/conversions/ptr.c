/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:39:36 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/28 20:14:42 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t	_ft_printf_out_s(char *s, int fd);
size_t	_ft_printf_out_xX(char x, unsigned int nb, int fd, int alt_form);

/** The function _ft_printf_out_p() writes the address addr in hexadecimal
 * to the file descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_p(size_t addr, int fd)
{
	return (_ft_printf_out_xX('x', addr, fd, 1));
}
