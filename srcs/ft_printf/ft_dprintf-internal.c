/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf-internal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:57 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/26 13:07:31 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

# define ASCII_0			48

/* The function ft_putstr_len() writes the string pointed to by s to the file
 * descriptor fd.
 * @returns The number of characters written. */
ssize_t	ft_putstr_len(char *s, int fd);

/* The function ft_putchar_len() writes the character c to the file descriptor
 * fd.
 * @returns The number of characters written. */
ssize_t	ft_putchar_len(char c, int fd);

/* The function ft_putint_len() writes the number nb to the file
 * descriptor fd.
 * @returns The number of characters written. */
ssize_t	ft_putint_len(int nb, int fd);

/* The function ft_putuint_len() writes the unsigned number nb to the file
 * descriptor fd.
 * @returns The number of characters written. */
ssize_t	ft_putuint_len(uint32_t nb, int fd);

/* The function ft_putint_len() writes the number fd in hexadecimal to the file
 * descriptor fd.
 * @returns The number of characters written. */
ssize_t	ft_puthex_len(char x, unsigned int nb, int fd);

ssize_t	ft_putaddr_len(size_t nb, int fd);

ssize_t	ft_putulong_len(size_t nb, int fd);

ssize_t	ft_putlong_len(long nb, int fd);

int		ft_dprintf_internal(int fd, const char *f, va_list *ap);

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
