/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:27 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:22:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	_ft_vdprintf_internal(int fd, const char *format, va_list ap);

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = _ft_vdprintf_internal(fd, format, ap);
	va_end(ap);
	return (done);
}
