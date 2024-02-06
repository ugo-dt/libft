/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:39:36 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/06 22:50:42 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

void  _ft_printf_create_hex_internal(char *s, char x, unsigned int nb, int alt, int length);

/** The function _ft_printf_create_p() writes the address addr in hexadecimal
 * to the file descriptor fd.
 * @returns The number of characters written. */
char	*_ft_printf_create_p(size_t addr, struct _specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;

	if (addr)
	{
		GET_NUMBER_LENGTH(&arg_length, addr, 16, specs->info.precision);
		arg_length += 2;
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		_ft_printf_create_hex_internal(s + arg_start,  'x', addr, 1, arg_length);
	}
	else
	{
		arg_length = 5;
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		ft_memcpy(s + arg_start, "(nil)", arg_length);
	}
	return (s);
}
