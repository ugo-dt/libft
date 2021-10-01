/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:06:59 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 12:18:10 by ugdaniel         ###   ########.fr       */
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

static char	*check_ptr(t_flags *flags, char *s)
{
	char	*dest;

	if (flags->specs[SPEC_PTR] || flags->flags[FLAG_HASH])
	{
		if (flags->flags[FLAG_UPPER])
			dest = ft_strjoin("0X", s);
		else
			dest = ft_strjoin("0x", s);
	}
	else
		dest = ft_strdup(s);
	free(s);
	return (dest);
}

char	*ft_itoa_hex(t_flags *flags, long value, int base)
{
	char	*s;
	int		size;
	char	*tab;
	long	tmp;

	tab = "0123456789abcdef";
	if (flags->flags[FLAG_UPPER])
		tab = "0123456789ABCDEF";
	tmp = value;
	size = 0;
	while (tmp && size++)
		tmp /= base;
	size++;
	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		return (NULL);
	s[size] = '\0';
	while (size > 0)
	{
		s[size - 1] = tab[value % base];
		size--;
		value /= base;
	}
	return (check_ptr(flags, s));
}

int	check_prec_zero(t_flags *flags, va_list args, int temp)
{
	va_list	args2;

	va_copy(args2, args);
	if (!flags->specs[SPEC_INT] && !flags->specs[SPEC_UINT]
		&& !flags->specs[SPEC_HEX] && !flags->specs[SPEC_PTR]
		&& flags->precision == 0 && flags->flags[FLAG_PREC])
	{
		if (va_arg(args2, int) == 0 && flags->width == 0)
		{
			temp = va_arg(args, int);
			va_end(args2);
			return (1);
		}
	}
	else if (flags->precision == 0 && flags->flags[FLAG_PREC])
	{
		if (va_arg(args2, int) == 0 && !flags->specs[SPEC_PTR])
		{
			temp = va_arg(args, int);
			va_end(args2);
			return (1);
		}
	}
	va_end(args2);
	return (0);
}
