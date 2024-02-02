/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:56:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 19:54:55 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

/* The function _ft_printf_out_s() writes the string pointed to by s to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_s(const char *s, int fd, int flag_left, int width)
{
	size_t	len, done;

	done = 0;
	if (s)
		len = ft_strlen(s);
	else
		len = 6;
	if (!flag_left)
		done += _add_padding(width, ' ', len, fd);
	if (s)
		done += write(fd, s, len);
	else
		done += write(fd, "(null)", 6);
	if (flag_left)
		done += _add_padding(width, ' ', done, fd);
	return (done);
}
