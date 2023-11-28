/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft__vdprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:57 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/28 20:41:04 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t _ft_printf_out_c(char c, int fd);
size_t _ft_printf_out_s(char *s, int fd);
size_t _ft_printf_out_p(size_t addr, int fd);
size_t _ft_printf_out_di(int nb, int fd);
size_t _ft_printf_out_u(uint32_t nb, int fd);
size_t _ft_printf_out_xX(char x, unsigned int nb, int fd, int flag_hash);
size_t _ft_printf_out_l(long nb, int fd);
size_t _ft_printf_out_ll(long nb, int fd);
size_t _ft_printf_out_ul(unsigned long nb, int fd);
size_t _ft_printf_out_ull(unsigned long nb, int fd);

/**
 * The format string is a character string, beginning and ending in its initial shift state, if any.
 * The format string is composed of zero or more directives:
 * 	ordinary characters (not %), which are copied unchanged to the output stream;
 * 	and conversion specifications, each of which results in fetching zero or more
    subsequent arguments. Each conversion specification is introduced by the character %,
	and ends with a conversion specifier. In between there may be (in this order)
	zero or more flags, an optional minimum field width, an optional precision and an optional length modifier.
*/
int _ft__vdprintf_internal(int fd, const char *f, va_list ap)
{
	int		done;
	int		flag_hash; // '#'. The value should be converted to an "alternate form".
	int		flag_zero;
	int		flag_minus;
	int		ell;
	va_list	ap_save;

	va_copy(ap_save, ap);
	done = 0;
	while (*f)
	{
		flag_hash = 0;
		flag_zero = 0;
		flag_minus = 0;
		ell = 0;
		if (*f != '%')
			done += _ft_printf_out_c(*f++, fd);
		else
		{
			f++;
			if (*f == '\0')
				break;
			if (*f == '#')
			{
				f++;
				flag_hash = 1;
			}
			if (*f == '0')
			{
				f++;
				flag_zero = 1;
			}
			// if (*f == '-')
			// {
			// 	f++;
			// 	flag_minus = 1;
			// 	flag_zero = 0;
			// }

			// field width
			// precision: If a precision is given with an integer conversion (d, i, o, u, x, and X), the 0 flag is ignored.

			if (*f == 'l')
			{
				f++;
				if (*f == 'l')
				{
					f++;
					ell = 1;
				}
				if (*f == 'u')
				{
					if (ell)
						done += _ft_printf_out_ull(va_arg(ap_save, unsigned long long), fd);
					else
						done += _ft_printf_out_ul(va_arg(ap_save, unsigned long), fd);
				}
				else if (*f == 'd' || *f == 'i')
				{
					if (ell)
						done += _ft_printf_out_ll(va_arg(ap_save, long long), fd);
					else
						done += _ft_printf_out_l(va_arg(ap_save, long), fd);
				}
			}
			else if (*f == '%')
				done += _ft_printf_out_c('%', fd);
			else if (*f == 'c')
				done += _ft_printf_out_c(va_arg(ap, int), fd);
			else if (*f == 's')
				done += _ft_printf_out_s(va_arg(ap, char *), fd);
			else if (*f == 'p')
				done += _ft_printf_out_p(va_arg(ap, size_t), fd);
			else if (*f == 'd' || *f == 'i')
				done += _ft_printf_out_di(va_arg(ap, int), fd);
			else if (*f == 'u')
				done += _ft_printf_out_u(va_arg(ap, uint32_t), fd);
			else if (*f == 'x' || *f == 'X')
			{
				done += _ft_printf_out_xX(*f, va_arg(ap, int), fd, flag_hash);
			}
			f++;
		}
	}
	return (done);
}
