/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_vdprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:57 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 19:03:12 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "conversions/_conversions.h"

/*
	todo
	flags
		alt
			For x and X conversions, a nonzero result has the string
              "0x" (or "0X" for X conversions) prepended to it
		zero
			For d, i, o, u, x, X, a,
              A, e, E, f, F, g, and G conversions, the converted value
              is padded on the left with zeros rather than blanks. If
              the 0 and - flags both appear, the 0 flag is ignored.  If
              a precision is given with an integer conversion (d, i, o,
              u, x, and X), the 0 flag is ignored.
		minus
		space
		plus
*/

/**
 * The format string is a character string, beginning and ending in its initial shift state, if any.
 * The format string is composed of zero or more directives:
 * 	ordinary characters (not %), which are copied unchanged to the output stream;
 * 	and conversion specifications, each of which results in fetching zero or more
	subsequent arguments. Each conversion specification is introduced by the character %,
	and ends with a conversion specifier. In between there may be (in this order)
	zero or more flags, an optional minimum field width, an optional precision and an optional length modifier.
*/
int _ft_vdprintf_internal(int fd, const char *format, va_list ap)
{
	int				done;
	unsigned char	*f;
	unsigned char	*lead_str_end;

	done = 0;
	f = lead_str_end = (unsigned char *)_ft_find_spec((const unsigned char *)format);
	if ((done = write(fd, format, (const unsigned char *)lead_str_end - (const unsigned char *)format)) < 0)
		return -1;
	while (*f != '\0')
	{
		if (*f != '%')
			done += _ft_printf_out_c_internal(*f++, fd);
		else
		{
			struct _specs specs = { 0 };
			f = _ft_find_flags(++f, &specs);
			if (*f == '\0')
				return (-1);

			// field width
			f = _ft_find_width(f, &specs.info.width);
			if (*f == '\0')
				return (-1);

			// precision: If a precision is given with an integer conversion (d, i, o, u, x, and X), the 0 flag is ignored.

			char	*s = NULL;
			if (*f == 'l')
			{
				int is_long = 0;
				f++;
				if (*f == 'l')
				{
					f++;
					is_long = 1;
				}
				if (*f == 'u')
				{
					if (is_long)
						s = _ft_printf_create_ull(va_arg(ap, unsigned long long), &specs);
					else
						s = _ft_printf_create_ul(va_arg(ap, unsigned long), &specs);
				}
				else if (*f == 'd' || *f == 'i')
				{
					if (is_long)
						s = _ft_printf_create_ll(va_arg(ap, long long), &specs);
					else
						s = _ft_printf_create_l(va_arg(ap, long), &specs);
				}
			}
			else if (*f == '%')
				s = _ft_printf_create_c('%', &specs);
			else if (*f == 'c')
				s = _ft_printf_create_c(va_arg(ap, int), &specs);
			else if (*f == 's')
				s = _ft_printf_create_s(va_arg(ap, char *), &specs);
			else if (*f == 'p')
				s = _ft_printf_create_p(va_arg(ap, size_t), &specs);
			else if (*f == 'd' || *f == 'i')
				s = _ft_printf_create_di(va_arg(ap, int), &specs);
			else if (*f == 'u')
				s = _ft_printf_create_u(va_arg(ap, unsigned int), &specs);
			else if (*f == 'x' || *f == 'X')
				s = _ft_printf_create_xX(*f, va_arg(ap, int), &specs);

			if (!s)
				return (-1);
			write(fd, s, specs.info.width);
			free(s);
			done += specs.info.width;
			f++;
		}
	}
	return (done);
}
