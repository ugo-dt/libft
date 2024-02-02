/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:06:10 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 19:28:01 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

/** The function _ft_printf_out_c_internal() writes the character c to the file descriptor
 * fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_c_internal(char c, int fd)
{
	return (write(fd, &c, 1));
}

size_t	_ft_printf_out_c(char c, int fd, int flag_left, int width)
{
	size_t done;

	done = 0;
	if (!flag_left)
		done += _add_padding(width, ' ', 1, fd);
	done += write(fd, &c, sizeof(c));
	if (flag_left)
		done += _add_padding(width, ' ', 1, fd);
	return (done);
}
