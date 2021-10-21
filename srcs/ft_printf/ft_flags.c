/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:06:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/21 19:48:30 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	check_flags(t_flags *flags);

/*
**	Looks for the following specifiers:
**		c	- char;
**		s	- string;
**		p	- pointer;
**		d,i	- int;
**		u	- unsigned int
**		x,X	- hex
**		%	- percent sign;
**	Sets 1 to the corresponding specifier in the array.
*/

const char	*get_specs(const char *f, t_flags *flags)
{
	if (*f == 'c')
		flags->specs[SPEC_CHAR] = 1;
	else if (*f == 's')
		flags->specs[SPEC_STR] = 1;
	else if (*f == 'p')
		flags->specs[SPEC_PTR] = 1;
	else if (*f == 'd' || *f == 'i')
		flags->specs[SPEC_INT] = 1;
	else if (*f == 'u')
		flags->specs[SPEC_UINT] = 1;
	else if (*f == 'x')
		flags->specs[SPEC_HEX] = 1;
	else if (*f == 'X')
	{
		flags->specs[SPEC_HEX] = 1;
		flags->flags[FLAG_UPPER] = 1;
	}
	else if (*f == '%')
		flags->specs[SPEC_PCENT] = 1;
	else
		flags->specs[SPEC_NONE] = 1;
	check_flags(flags);
	return (f);
}

/*
**	Looks for a given precision in the inputted string,
**	then goes on to the specifiers.
*/

const char	*get_prec_field(const char *f, t_flags *flags, va_list va)
{
	int		p;

	while (*f == '*' || *f == '-' || ft_isdigit(*f))
		f++;
	if (*f == '.')
	{
		flags->flags[FLAG_PREC] = 1;
		f++;
		if (ft_isdigit(*f))
			flags->precision = ft_atoi(f);
		else if (*f == '*')
		{
			p = va_arg(va, int);
			if (p < 0)
				flags->flags[FLAG_PREC] = 0;
			else
				flags->precision = (unsigned int)p;
			f++;
		}
	}
	while (*f == '*' || *f == '.' || ft_isdigit(*f))
		f++;
	return (get_specs(f, flags));
}

/*
**	Looks for a given width_field in the inputted string.
**	then goes on to the precision.
*/

const char	*get_width_field(const char *f, t_flags *flags, va_list va)
{
	int	w;

	if (ft_isdigit(*f) || *f == '-')
	{
		if (*f == '-' && f + 1)
		{
			f++;
			flags->flags[FLAG_MINUS] = 1;
		}
		flags->width = ft_atoi(f);
	}
	else if (*f == '*')
	{
		w = va_arg(va, int);
		if (w < 0)
		{
			flags->flags[FLAG_LEFT] = 1;
			flags->width = -w;
		}
		else
			flags->width = w;
		f++;
	}
	return (get_prec_field(f, flags, va));
}

/*
**	Looks for flags given in the inputted string.
**	Sets 1 to the corresponding flags in the array,
**	then goes on to the width field.
*/

const char	*get_flags(const char *f, t_flags *flags, va_list va)
{
	int		loop;

	loop = 1;
	while (loop)
	{
		if (*f == '0')
			flags->flags[FLAG_ZERO] = 1;
		else if (*f == '-')
			flags->flags[FLAG_MINUS] = 1;
		else if (*f == '+')
			flags->flags[FLAG_PLUS] = 1;
		else if (*f == ' ')
			flags->flags[FLAG_SPACE] = 1;
		else if (*f == '#')
			flags->flags[FLAG_HASH] = 1;
		else
			loop = 0;
		if (loop)
			f++;
	}
	return (get_width_field(f, flags, va));
}

/*
**	Initializes and zeroes the specifiers and flags arrays,
**	as well as the width and precision.
*/

void	init_flags(t_flags *flags)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < NB_SPECS && j < NB_FLAGS)
	{
		flags->specs[i++] = 0;
		flags->flags[j++] = 0;
	}
	flags->width = 0;
	flags->precision = 0;
}
