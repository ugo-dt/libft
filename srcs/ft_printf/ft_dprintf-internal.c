/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf-internal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:57 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/23 20:42:48 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdarg.h>

ssize_t	convert_identifier(int fd, const char *f, va_list *ap)
{
	if (*f == '%')
		return (ft_putchar_len('%', fd));
	else if (*f == 'c')
		return (ft_putchar_len(va_arg(*ap, int), fd));
	else if (*f == 's')
		return (ft_putstr_len(va_arg(*ap, char *), fd));
	else if (*f == 'p')
		return (ft_putstr_len("0x\0", fd)
			+ ft_putaddr_len(va_arg(*ap, size_t), fd));
	else if (*f == 'd' || *f == 'i')
		return (ft_putint_len(va_arg(*ap, int), fd));
	else if (*f == 'u')
		return (ft_putuint_len(va_arg(*ap, uint32_t), fd));
	else if (*f == 'x' || *f == 'X')
		return (ft_puthex_len(*f, va_arg(*ap, int), fd));
	return (0);
}

int	ft_dprintf_internal(int fd, const char *f, va_list *ap)
{
	int		done;

	done = 0;
	while (*f)
	{
		if (*f != '%')
			done += ft_putchar_len(*f++, fd);
		else
		{
			f++;
			if (*f == 'l')
			{
				f++;
				if (*f == 'u')
					done += ft_putulong_len(va_arg(*ap, size_t), fd);
				else if (*f == 'd' || *f == 'i')
					done += ft_putlong_len(va_arg(*ap, long), fd);
			}
			else
				done += convert_identifier(fd, f, ap);
			f++;
		}
	}
	return (done);
}
