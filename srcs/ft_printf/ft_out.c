/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:06:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 12:21:13 by ugdaniel         ###   ########.fr       */
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

void	init_flags(t_flags *flags);
void	check_flags(t_flags *flags);
char	*add_zeros_int(t_flags *flags, char *s);

static char	*add_spaces(t_flags *flags, char *s, int size)
{
	char	*temp;
	char	*dest;

	if (!s || size < 0)
		return (s);
	temp = (char *)malloc(sizeof(char) * size + 1);
	if (!temp)
		return (s);
	temp = ft_memset(temp, ' ', size);
	temp[size] = '\0';
	dest = s;
	if (!flags->flags[FLAG_LEFT] && !flags->flags[FLAG_MINUS])
		dest = ft_strjoin(temp, s);
	else if (flags->flags[FLAG_LEFT] || flags->flags[FLAG_MINUS])
		dest = ft_strjoin(s, temp);
	free(temp);
	free(s);
	return (dest);
}

char	*add_padding(t_flags *fl, char *s)
{
	if (fl->flags[FLAG_PREC] && fl->precision < (int)ft_strlen(s)
		&& fl->specs[SPEC_STR])
		s = ft_strncpy(s, s, fl->precision);
	if (fl->specs[SPEC_INT] || fl->specs[SPEC_UINT]
		|| fl->specs[SPEC_HEX] || fl->specs[SPEC_PCENT])
	{
		if (fl->flags[FLAG_PREC] || fl->flags[FLAG_ZERO])
			s = add_zeros_int(fl, s);
		if (fl->width > (int)ft_strlen(s))
			s = add_spaces(fl, s, fl->width - ft_strlen(s));
	}
	else if (fl->specs[SPEC_CHAR] || fl->specs[SPEC_STR]
		|| fl->specs[SPEC_PTR] || fl->specs[SPEC_PCENT])
	{
		if (fl->flags[FLAG_ZERO])
			s = add_zeros_int(fl, s);
		if (fl->width)
			s = add_spaces(fl, s, fl->width - ft_strlen(s));
	}
	return (s);
}

static int	check_char(t_flags *flags, char *s, int fd, int ret)
{
	if (s[0] == '\0')
	{
		s[0] = ' ';
		s = add_padding(flags, s);
		if (!flags->flags[FLAG_LEFT] && !flags->flags[FLAG_MINUS])
		{
			write(fd, s, ft_strlen(s) - 1);
			write(fd, "\0", 1);
		}
		else if (flags->flags[FLAG_LEFT] || flags->flags[FLAG_MINUS])
		{
			write(fd, "\0", 1);
			write(fd, s, ft_strlen(s) - 1);
		}
	}
	else
	{
		s = add_padding(flags, s);
		ft_putstr_fd(s, fd);
	}
	ret += ft_strlen(s);
	free(s);
	return (ret);
}

int	out(t_flags *flags, char *s, int fd)
{
	int		ret;

	ret = 0;
	if (flags->specs[SPEC_CHAR])
	{
		ret += check_char(flags, s, fd, 0);
		init_flags(flags);
		if (ret)
			return (ret);
	}
	s = add_padding(flags, s);
	ft_putstr_fd(s, fd);
	ret += ft_strlen(s);
	free(s);
	init_flags(flags);
	return (ret);
}
