/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:06:10 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 20:27:52 by ugdaniel         ###   ########.fr       */
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

char	*_ft_printf_create_c(char c, struct _specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;
	
	arg_length = 1;
	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
	ft_memset(s + arg_start, c, arg_length);
	return (s);
}
