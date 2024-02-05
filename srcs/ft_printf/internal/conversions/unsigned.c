/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:56:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 19:43:16 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "_conversions.h"

# define _UNSIGNED_DECL(_name, _type) \
	int	_ft_printf_out_##_name(_type nb, int fd, struct _specs *specs) \
	{ \
		int arg_length; \
		int arg_start; \
		char *s; \
		 \
		GET_NUMBER_LENGTH(&arg_length, nb, 10); \
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start); \
		MAKE_UNSIGNED_NUMBER_STRING(s + arg_start, nb, arg_length); \
		write(fd, s, specs->info.width); \
		free(s); \
		return (specs->info.width); \
	};

_UNSIGNED_DECL(u, unsigned int)
_UNSIGNED_DECL(ul, unsigned long)
_UNSIGNED_DECL(ull, unsigned long long)
