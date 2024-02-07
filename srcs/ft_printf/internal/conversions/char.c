/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:06:10 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/07 13:08:28 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_conversions.h"

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
