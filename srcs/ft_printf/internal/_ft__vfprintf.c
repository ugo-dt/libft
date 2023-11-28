/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft__vfprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:38:44 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/28 15:44:00 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

ssize_t	ft_putchar_size(char c, FILE* stream);
ssize_t	ft_putstr_size(char *s, FILE* stream);
ssize_t	ft_putaddr_size(size_t addr, FILE* stream);
ssize_t	ft_putint_size(int nb, FILE* stream);
ssize_t	ft_putuint_size(uint32_t nb, FILE* stream);
ssize_t	ft_puthex_size(char x, unsigned int nb, FILE* stream);
ssize_t	ft_putulong_size(size_t nb, FILE* stream);
ssize_t	ft_putlong_size(long nb, FILE* stream);

static ssize_t	convert_identifier(FILE* stream, const char *f, va_list *ap)
{
	if (*f == '%')
		return (ft_putchar_size('%', stream));
	else if (*f == 'c')
		return (ft_putchar_size(va_arg(*ap, int), stream));
	else if (*f == 's')
		return (ft_putstr_size(va_arg(*ap, char *), stream));
	else if (*f == 'p')
		return (ft_putaddr_size(va_arg(*ap, size_t), stream));
	else if (*f == 'd' || *f == 'i')
		return (ft_putint_size(va_arg(*ap, int), stream));
	else if (*f == 'u')
		return (ft_putuint_size(va_arg(*ap, uint32_t), stream));
	else if (*f == 'x' || *f == 'X')
		return (ft_puthex_size(*f, va_arg(*ap, int), stream));
	return (0);
}

int	_ft__vfprintf_internal(FILE* stream, const char *f, va_list ap)
{
	int		done;

	done = 0;
	while (*f)
	{
		if (*f != '%')
			done += ft_putchar_size(*f++, stream);
		else
		{
			f++;
			if (*f == '\0')
				break ;
			if (*f == 'l')
			{
				f++;
				if (*f == 'u')
					done += ft_putulong_size(va_arg(ap, size_t), stream);
				else if (*f == 'd' || *f == 'i')
					done += ft_putlong_size(va_arg(ap, long), stream);
			}
			else
				done += convert_identifier(stream, f, ap);
			f++;
		}
	}
	return (done);
}
