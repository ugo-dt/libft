/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_internal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:06:57 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 12:10:23 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

#define NB_SPECS	8
#define NB_FLAGS	8

#define SPEC_CHAR	0
#define SPEC_STR	1
#define SPEC_PTR	2
#define SPEC_INT	3
#define SPEC_UINT	4
#define SPEC_HEX	5
#define SPEC_PCENT	6
#define SPEC_NONE	7

#define FLAG_ZERO	0
#define FLAG_MINUS	1
#define FLAG_PLUS	2
#define FLAG_SPACE	3
#define FLAG_HASH	4
#define FLAG_LEFT	5
#define FLAG_PREC	6
#define FLAG_UPPER	7

typedef struct s_flags
{
	unsigned int	specs[NB_SPECS];
	unsigned int	flags[NB_FLAGS];
	int				width;
	int				precision;
}t_flags;

void		init_flags(t_flags *flags);
void		check_flags(t_flags *flags);
const char	*get_flags(const char *format, t_flags *flags, va_list va);
char		*ft_itoa_hex(t_flags *flags, long value, int base);
int			check_prec_zero(t_flags *flags, va_list args, int temp);
void		join(char *s1, char *s2);
void		join2(char *s1, char *s2);
int			out(t_flags *flags, char *s, int fd);

static char	*get_str(t_flags *flags, va_list va)
{
	char	*s;

	s = NULL;
	if (flags->specs[SPEC_CHAR])
	{
		s = ft_strdup("a");
		s[0] = va_arg(va, int);
	}
	else if (flags->specs[SPEC_STR])
		s = ft_strdup(va_arg(va, char *));
	else if (flags->specs[SPEC_PTR])
		s = ft_itoa_hex(flags, va_arg(va, unsigned long), 16);
	else if (flags->specs[SPEC_INT])
		s = ft_itoa(va_arg(va, int));
	else if (flags->specs[SPEC_HEX] == 1)
		s = ft_itoa_hex(flags, va_arg(va, unsigned int), 16);
	else if (flags->specs[SPEC_UINT] == 1)
		s = ft_itoa(va_arg(va, unsigned int));
	else if (flags->specs[SPEC_PCENT] == 1)
		s = ft_strdup("%");
	if (!s)
		s = ft_strdup("(null)");
	return (s);
}

static int	ft_conversion(int fd, t_flags *flags, va_list va)
{
	int		ret;

	if (check_prec_zero(flags, va, 0))
		return (out(flags, ft_strdup(""), fd));
	ret = 0;
	ret += out(flags, get_str(flags, va), fd);
	return (ret);
}

static int	ft_process_str(int fd, const char *format, va_list va)
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
			format = get_flags(format, &flags, va);
			ret += ft_conversion(fd, &flags, va);
			format++;
		}
	}
	return (ret);
}

int	ft_dprintf_internal(int fd, const char *format, va_list args)
{
	int		ret;

	ret = 0;
	if (format)
		ret = ft_process_str(fd, format, args);
	return (ret);
}
