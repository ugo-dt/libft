/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:23:32 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 20:29:14 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

# define _SIGNED_DECL(_name, _type) \
	char	*_ft_printf_create_##_name(_type nb, struct _specs *specs) \
	{ \
		int arg_length; \
		int arg_start; \
		char *s; \
		GET_NUMBER_LENGTH(&arg_length, nb, 10); \
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start); \
		MAKE_NUMBER_STRING(s + arg_start, _type, ft_##_name##abs, nb, arg_length); \
		return (s); \
	}

#define ft_diabs ft_abs
_SIGNED_DECL(di, int)
#undef ft_diabs
_SIGNED_DECL(l, long)
_SIGNED_DECL(ll, long long)
