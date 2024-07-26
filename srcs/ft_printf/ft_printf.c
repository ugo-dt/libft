/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:48:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:22:37 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	_ft_vdprintf_internal(int fd, const char *format, va_list ap);

int	ft_printf(const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = _ft_vdprintf_internal(STDOUT_FILENO, format, ap);
	va_end(ap);
	return (done);
}
