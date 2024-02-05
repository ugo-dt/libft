/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:56:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/03 14:54:22 by ugdaniel         ###   ########.fr       */
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
	_ADD_PADDING_SPACES(
	if (s)
		done += write(fd, s, len);
	else
		done += write(fd, "(null)", 6);
	);
	return (done);
}
