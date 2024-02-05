/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_vsnprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:33:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 21:13:12 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"
#include "conversions/_conversions.h"

/**
 * The format string is a character string, beginning and ending in its initial shift state, if any.
 * The format string is composed of zero or more directives:
 * 	ordinary characters (not %), which are copied unchanged to the output stream;
 * 	and conversion specifications, each of which results in fetching zero or more
	subsequent arguments. Each conversion specification is introduced by the character %,
	and ends with a conversion specifier. In between there may be (in this order)
	zero or more flags, an optional minimum field width, an optional precision and an optional length modifier.
*/
int	ft_vsnprintf_internal(char *s, size_t maxlen, const char *format, va_list ap)
{
	int				done;
	unsigned char	*f;
	unsigned char	*lead_str_end;
	size_t			curr_len;
	long			len;

	ft_memset(s, 0, maxlen);
	curr_len = 0;
	done = 0;
	f = lead_str_end = (unsigned char *)_ft_find_spec((const unsigned char *)format);
	len = min((const unsigned char *)lead_str_end - (const unsigned char *)format, (long)maxlen - 1);
	ft_strncat(s, format, len);
	curr_len += len;
	while (*f != '\0' && curr_len < maxlen)
	{
		if (*f != '%')
		{
			ft_strncat(s, (const char *)f++, 1);
			curr_len++;
		}
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

			char	*out = NULL;
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
						out = _ft_printf_create_ull(va_arg(ap, unsigned long long), &specs);
					else
						out = _ft_printf_create_ul(va_arg(ap, unsigned long), &specs);
				}
				else if (*f == 'd' || *f == 'i')
				{
					if (is_long)
						out = _ft_printf_create_ll(va_arg(ap, long long), &specs);
					else
						out = _ft_printf_create_l(va_arg(ap, long), &specs);
				}
			}
			else if (*f == '%')
				out = _ft_printf_create_c('%', &specs);
			else if (*f == 'c')
				out = _ft_printf_create_c(va_arg(ap, int), &specs);
			else if (*f == 's')
				out = _ft_printf_create_s(va_arg(ap, char *), &specs);
			else if (*f == 'p')
				out = _ft_printf_create_p(va_arg(ap, size_t), &specs);
			else if (*f == 'd' || *f == 'i')
				out = _ft_printf_create_di(va_arg(ap, int), &specs);
			else if (*f == 'u')
				out = _ft_printf_create_u(va_arg(ap, unsigned int), &specs);
			else if (*f == 'x' || *f == 'X')
				out = _ft_printf_create_xX(*f, va_arg(ap, int), &specs);
			if (!out)
				return (-1);
			len = min(maxlen - 1 - curr_len, specs.info.width + curr_len);
			ft_strncat(s, out, len);
			done += len;
			curr_len += len;
			free(out);
			f++;
		}
	}
	return (done);
}
