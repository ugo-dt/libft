/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:03:20 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 19:47:19 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

// /** The function _ft_printf_out_l() writes the long number nb to the file
//  * descriptor fd.
//  * @returns The number of characters written. */
// int	_ft_printf_out_l(long nb, int fd, struct _specs *specs)
// {
// 	int arg_length;
// 	int arg_start;
// 	char *s;
	
// 	GET_NUMBER_LENGTH(&arg_length, nb, 10);
// 	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
// 	MAKE_NUMBER_STRING(s + arg_start, long, ft_labs, nb, arg_length);
// 	write(fd, s, specs->info.width);
// 	free(s);
// 	return (specs->info.width);
// }

// int	_ft_printf_out_ll(long long nb, int fd, struct _specs *specs)
// {
// 	int arg_length;
// 	int arg_start;
// 	char *s;
	
// 	GET_NUMBER_LENGTH(&arg_length, nb, 10);
// 	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
// 	MAKE_NUMBER_STRING(s + arg_start, long long, ft_llabs, nb, arg_length);
// 	write(fd, s, specs->info.width);
// 	free(s);
// 	return (specs->info.width);
// }
