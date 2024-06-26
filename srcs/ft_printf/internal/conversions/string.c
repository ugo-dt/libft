/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:56:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/05 11:11:21 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_conversions.h"

/** The function _ft_printf_create_s() writes the string pointed to by str to the file
 * descriptor fd.
 * @returns The number of characters written. */
char	*_ft_printf_create_s(const char *str, struct _specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;

	if (str)
	{
		if (specs->info.precision > -1)
			arg_length = min((int)ft_strlen(str), specs->info.precision);
		else
			arg_length = ft_strlen(str);
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		ft_memcpy(s + arg_start, str, arg_length);
	}
	else
	{
		arg_length = sizeof(_ft_printf__null_string) - 1; // Remove the null character
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		ft_memcpy(s + arg_start, _ft_printf__null_string, arg_length);
	}
	return (s);
}
