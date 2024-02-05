/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:56:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 19:31:27 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

/** The function _ft_printf_out_s() writes the string pointed to by str to the file
 * descriptor fd.
 * @returns The number of characters written. */
int	_ft_printf_out_s(const char *str, int fd, struct _specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;

	if (str)
	{
		arg_length = ft_strlen(str);
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		ft_memcpy(s + arg_start, str, arg_length);
	}
	else
	{
		arg_length = 6;
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		ft_memcpy(s + arg_start, "(null)", 6);
	}
	write(fd, s, specs->info.width);
	free(s);
	return (specs->info.width);
}
