/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_internal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:06:57 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/06 13:01:05 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "_ft_printf.h"

void		init_flags(t_flags *flags);
void		check_flags(t_flags *flags);
const char	*get_flags(const char *format, t_flags *flags, va_list *args);
char		*ft_itoa_hex(t_flags *flags, long value, int base);
int			check_prec_zero(t_flags *flags, va_list *args, int temp);
void		join(char *s1, char *s2);
void		join2(char *s1, char *s2);
int			out(t_flags *flags, char *s, int fd);

static char	*get_str(t_flags *flags, va_list *args)
{
	char	*s;

	s = NULL;
	if (flags->specs[SPEC_CHAR])
	{
		s = ft_strdup("a");
		s[0] = va_arg(*args, int);
	}
	else if (flags->specs[SPEC_STR])
		s = ft_strdup(va_arg(*args, char *));
	else if (flags->specs[SPEC_PTR])
		s = ft_itoa_hex(flags, va_arg(*args, unsigned long), 16);
	else if (flags->specs[SPEC_INT])
		s = ft_itoa(va_arg(*args, int));
	else if (flags->specs[SPEC_HEX] == 1)
		s = ft_itoa_hex(flags, va_arg(*args, unsigned int), 16);
	else if (flags->specs[SPEC_UINT] == 1)
		s = ft_itoa(va_arg(*args, unsigned int));
	else if (flags->specs[SPEC_PCENT] == 1)
		s = ft_strdup("%");
	if (!s)
		s = ft_strdup("(null)");
	return (s);
}

static int	ft_conversion(int fd, t_flags *flags, va_list *args)
{
	int		ret;

	if (check_prec_zero(flags, args, 0))
		return (out(flags, ft_strdup(""), fd));
	ret = 0;
	ret += out(flags, get_str(flags, args), fd);
	return (ret);
}

static int	ft_process_str(int fd, const char *format, va_list *args)
{
	int			ret;
	t_flags		flags;

	init_flags(&flags);
	ret = 0;
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format++, fd);
			ret++;
		}
		else
		{
			format++;
			format = get_flags(format, &flags, args);
			ret += ft_conversion(fd, &flags, args);
			format++;
		}
	}
	return (ret);
}

int	ft_dprintf_internal(int fd, const char *format, va_list *args)
{
	int		ret;

	ret = 0;
	if (format)
		ret = ft_process_str(fd, format, args);
	return (ret);
}
