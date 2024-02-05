/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:06:10 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/03 19:31:04 by ugdaniel         ###   ########.fr       */
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
	char *s;
	int	arg_length;
	size_t full_length;

	arg_length = 1;
	if (width < arg_length)
		width = arg_length;
	full_length = width;
	CREATE_STRING(s, full_length, width - arg_length, flag_left, 0,
	APPEND_CHAR(c, arg_length);
	);

	write(fd, s, full_length);
	free(s);
	return (width);
}
