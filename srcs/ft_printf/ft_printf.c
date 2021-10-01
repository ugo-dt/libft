/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 11:02:12 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 11:02:12 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

int	ft_dprintf_internal(int fd, const char *format, va_list args);

int	ft_dprintf(int fd, const char *format, ...)
{
	int		done;
	va_list	args;

	va_start(args, format);
	done = ft_dprintf_internal(fd, format, args);
	va_end(args);
	return (done);
}

int	ft_printf(const char *format, ...)
{
	int		done;
	va_list	args;

	va_start(args, format);
	done = ft_dprintf_internal(STDOUT_FILENO, format, args);
	va_end(args);
	return (done);
}
