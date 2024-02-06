/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:23:32 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/06 21:40:47 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

# define _SIGNED_CONVERSION_DEF(_name, _type) \
	char	*_ft_printf_create_##_name(_type nb, struct _specs *specs) \
	{ \
		int arg_length; \
		int arg_start; \
		char *s; \
		GET_NUMBER_LENGTH(&arg_length, nb, 10, specs->info.precision); \
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start); \
		MAKE_NUMBER_STRING(s + arg_start, _type, ft_##_name##abs, nb, arg_length); \
		return (s); \
	}

#define ft_diabs ft_abs
_SIGNED_CONVERSION_DEF(di, int)
#undef ft_diabs
_SIGNED_CONVERSION_DEF(l, long)
_SIGNED_CONVERSION_DEF(ll, long long)
