/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:56:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/08 17:14:18 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_conversions.h"

# define _UNSIGNED_CONVERSION_DEF(_name, _type) \
	char	*_ft_printf_create_##_name(_type nb, struct _specs *specs) \
	{ \
		int arg_length; \
		int arg_start; \
		char *s; \
		 \
		GET_NUMBER_LENGTH(&arg_length, nb, 10, specs->info.precision, _type); \
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start); \
		MAKE_UNSIGNED_NUMBER_STRING(s + arg_start, nb, arg_length, _type); \
		return (s); \
	}

_UNSIGNED_CONVERSION_DEF(u, unsigned int)
_UNSIGNED_CONVERSION_DEF(ul, unsigned long)
_UNSIGNED_CONVERSION_DEF(ull, unsigned long long)
