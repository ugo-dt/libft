/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _conversions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:51:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 20:34:56 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONVERSIONS_H
# define _CONVERSIONS_H

# include <stdlib.h>

typedef enum
{
	false,
	true
}bool;

struct _specs
{
	struct
	{
		bool	alt:1;
		bool	zero:1;
		bool	left:1;
		bool	space:1;
		bool	showsign:1;
	}flags;

	struct
	{
		int	width;
	}info;
};

int		_ft_printf_out_c_internal(char c, int fd);
char	*_ft_printf_create_c(char c, struct _specs *specs);
char	*_ft_printf_create_s(const char *s, struct _specs *specs);
char	*_ft_printf_create_p(size_t addr, struct _specs *specs);
char	*_ft_printf_create_di(int nb, struct _specs *specs);
char	*_ft_printf_create_u(unsigned int nb, struct _specs *specs);
void	_ft_printf_create_hex_internal(char *s, char x, unsigned int nb, int alt, int length);
char	*_ft_printf_create_xX(char x, unsigned int nb, struct _specs *specs);
char	*_ft_printf_create_l(long nb, struct _specs *specs);
char	*_ft_printf_create_ll(long long nb, struct _specs *specs);
char	*_ft_printf_create_ul(unsigned long nb, struct _specs *specs);
char	*_ft_printf_create_ull(unsigned long long nb, struct _specs *specs);

__extern_always_inline const unsigned char	*_ft_find_spec(const unsigned char *format)
{
	const unsigned char	*c = (const unsigned char *)ft_strchr((const char *)format, '%');
	if (!c)
		return format + ft_strlen((const char *)format);
	return (c);
}

__extern_always_inline unsigned char *_ft_find_width(unsigned char *f, int *width)
{
	*width = 0;
	if (ft_isdigit(*f))
	{
		*width = ft_atoi((const char *)f);
		while (ft_isdigit(*f) && *f)
			f++;
	}
	return f;
}

__extern_always_inline unsigned char *_ft_find_flags(unsigned char *f, struct _specs *specs)
{
	while (ft_strchr("#0- +", *f) && *f)
	{
		if (*f == '#')
		{
			specs->flags.alt = 1;
		}
		if (*f == '0')
		{
			specs->flags.zero = 1;
		}
		if (*f == '-')
		{
			specs->flags.left = 1;
			specs->flags.zero = 0;
		}
		f++;
	}
	return f;
}

# define GET_NUMBER_LENGTH(_len_ptr, _nb, _base) \
	do \
	{ \
		(*(_len_ptr)) = 1; \
		typeof(_nb) _tmp = _nb; \
		if (_tmp < 0) \
		{ \
			(*(_len_ptr))++; \
			_tmp = -_tmp; \
		} \
		while (_tmp >= _base) \
		{ \
			_tmp /= _base; \
			(*(_len_ptr))++; \
		} \
	} while (0)

# define MAKE_UNSIGNED_NUMBER_STRING(s, _n, _length) \
	do \
	{ \
		char	*_s = (s); \
		int _i = _length - 1; \
		typeof(_n) _nb = _n; \
		while (_nb >= 10) \
		{ \
			_s[_i] = _nb % 10 + 48; \
			_nb /= 10; \
			_i--; \
		} \
		_s[_i] = _nb % 10 + 48; \
	} while (0)

# define MAKE_NUMBER_STRING(s, _type, _abs_f, _n, _length) \
	do \
	{ \
		char	*_s = (s); \
		int _i; \
		unsigned _type _nb; \
		if (_n < 0) \
			_s[0] = '-'; \
		_i = _length - 1; \
		_nb = _abs_f(_n); \
		while (_nb >= 10) \
		{ \
			_s[_i] = _nb % 10 + 48; \
			_nb /= 10; \
			_i--; \
		} \
		_s[_i] = _nb % 10 + 48; \
	} while (0)

static inline char *_ft_printf_create_string_helper(struct _specs *specs, int arg_length, int *arg_start)
{
	char *s;

	if (specs->info.width < arg_length)
		specs->info.width = arg_length;
	s = malloc(sizeof(char) * specs->info.width);
	if (!s)
		return (NULL);
	int padding_length = specs->info.width - arg_length;
	int padding_start;
	if (!specs->flags.left)
	{
		padding_start = 0;
		*arg_start = padding_length;
	}
	else
	{
		padding_start = arg_length;
		*arg_start = 0;
	}
	ft_memset(s + padding_start, specs->flags.zero ? '0' : ' ', padding_length);
	return (s);
}

#endif // _CONVERSIONS_H
