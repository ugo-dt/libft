/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:06:10 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 15:23:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

/** The function _ft_printf_out_c_internal() writes the character c to the file descriptor
 * fd.
 * @returns The number of characters written. */
int	_ft_printf_out_c_internal(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	_ft_printf_out_c(char c, int fd, struct _specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;
	
	arg_length = 1;
	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
	ft_memset(s + arg_start, c, arg_length);
	write(fd, s, specs->info.width);
	free(s);
	return (specs->info.width);
}
