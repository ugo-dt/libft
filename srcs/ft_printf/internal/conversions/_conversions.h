/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _conversions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:51:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/07 10:41:51 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONVERSIONS_H
#define _CONVERSIONS_H

#include <stdlib.h>

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
		int width;
		int precision;
	}info;
};

char *_ft_printf_create_c(char c, struct _specs *specs);
char *_ft_printf_create_s(const char *s, struct _specs *specs);
char *_ft_printf_create_p(size_t addr, struct _specs *specs);
char *_ft_printf_create_di(int nb, struct _specs *specs);
char *_ft_printf_create_u(unsigned int nb, struct _specs *specs);
char *_ft_printf_create_xX(char x, unsigned int nb, struct _specs *specs);
char *_ft_printf_create_l(long nb, struct _specs *specs);
char *_ft_printf_create_ll(long long nb, struct _specs *specs);
char *_ft_printf_create_ul(unsigned long nb, struct _specs *specs);
char *_ft_printf_create_ull(unsigned long long nb, struct _specs *specs);

__extern_always_inline const unsigned char *_ft_find_spec(const unsigned char *format)
{
	const unsigned char *c = (const unsigned char *)ft_strchr((const char *)format, '%');
	if (!c)
		return format + ft_strlen((const char *)format);
	return (c);
}

#define FIND_WIDTH(_f, _specs, _ap)                        \
	do                                                     \
	{                                                      \
		_specs.info.width = 0;                             \
		if (ft_isdigit(*_f))                               \
		{                                                  \
			_specs.info.width = ft_atoi((const char *)_f); \
			while (ft_isdigit(*_f) && *_f)                 \
				_f++;                                      \
		}                                                  \
		else if (*_f == '*')                               \
		{                                                  \
			int _w = va_arg(_ap, int);                     \
			if (_w < 0)                                    \
			{                                              \
				_specs.flags.left = true;                  \
				_specs.info.width = -_w;                   \
			}                                              \
			else                                           \
				_specs.info.width = _w;                    \
			_f++;                                          \
		}                                                  \
		if (*_f == '\0')                                   \
			return (-1);                                   \
	} while (0)

#define FIND_PRECISION(_f, _specs, _ap)                           \
	do                                                            \
	{                                                             \
		_specs.info.precision = -1;                               \
		while (*_f == '*' || *_f == '-' || ft_isdigit(*_f))       \
			_f++;                                                 \
		if (*_f == '.')                                           \
		{                                                         \
			_specs.info.precision = 1;                            \
			_f++;                                                 \
			if (ft_isdigit(*_f))                                  \
				_specs.info.precision = ft_atoi((const char *)f); \
			else if (*_f == '*')                                  \
			{                                                     \
				int _p = va_arg(_ap, int);                        \
				_specs.info.precision = _p < 0 ? 0 : _p;          \
				_f++;                                             \
			}                                                     \
		}                                                         \
		while (*_f == '*' || *_f == '.' || ft_isdigit(*_f))       \
			_f++;                                                 \
		if (_specs.info.precision > -1)                           \
			_specs.flags.zero = false;                            \
		if (*_f == '\0')                                          \
			return (-1);                                          \
	} while (0)

#define FIND_FLAGS(_f, _specs)                 \
	do                                         \
	{                                          \
		_f++;                                  \
		while (ft_strchr("#0- +", *_f) && *_f) \
		{                                      \
			if (*_f == '#')                    \
			{                                  \
				_specs.flags.alt = true;       \
			}                                  \
			if (*_f == '0')                    \
			{                                  \
				_specs.flags.zero = true;      \
			}                                  \
			if (*_f == '-')                    \
			{                                  \
				_specs.flags.left = true;      \
				_specs.flags.zero = false;     \
			}                                  \
			if (*_f == ' ')                    \
			{                                  \
				_specs.flags.space = true;     \
			}                                  \
			if (*_f == '+')                    \
			{                                  \
				_specs.flags.showsign = true;  \
				_specs.flags.space = false;    \
			}                                  \
			_f++;                              \
		}                                      \
	} while (0)

#define GET_NUMBER_LENGTH(_len_ptr, _nb, _base, _precision)     \
	do                                                          \
	{                                                           \
		(*(_len_ptr)) = 1;                                      \
		typeof(_nb) _tmp = _nb;                                 \
		if (_tmp < 0)                                           \
		{                                                       \
			(*(_len_ptr))++;                                    \
			_tmp = -_tmp;                                       \
		}                                                       \
		while (_tmp >= _base)                                   \
		{                                                       \
			_tmp /= _base;                                      \
			(*(_len_ptr))++;                                    \
		}                                                       \
		if (_nb < 0)                                            \
		{                                                       \
			if (_precision > -1 && (*(_len_ptr)) <= _precision) \
				(*(_len_ptr)) = _precision + 1;                 \
		}                                                       \
		else                                                    \
		{                                                       \
			if (_precision > -1 && (*(_len_ptr)) < _precision)  \
				(*(_len_ptr)) = _precision;                     \
		}                                                       \
	} while (0)

#define MAKE_UNSIGNED_NUMBER_STRING(s, _n, _length) \
	do                                              \
	{                                               \
		char *_s = (s);                             \
		int _i = _length - 1;                       \
		typeof(_n) _nb = _n;                        \
		while (_nb >= 10)                           \
		{                                           \
			_s[_i] = _nb % 10 + 48;                 \
			_nb /= 10;                              \
			_i--;                                   \
		}                                           \
		_s[_i] = _nb % 10 + 48;                     \
		_i--;                                       \
		while (_i >= 0)                             \
			_s[_i--] = '0';                         \
	} while (0)

#define MAKE_NUMBER_STRING(s, _type, _abs_f, _n, _length) \
	do                                                    \
	{                                                     \
		char *_s = (s);                                   \
		int _i;                                           \
		unsigned _type _nb;                               \
		if ((_n < 0))                                     \
			_s[0] = '-';                                  \
		_i = _length - 1;                                 \
		_nb = _abs_f(_n);                                 \
		while (_nb >= 10)                                 \
		{                                                 \
			_s[_i] = _nb % 10 + 48;                       \
			_nb /= 10;                                    \
			_i--;                                         \
		}                                                 \
		_s[_i] = _nb % 10 + 48;                           \
		_i--;                                             \
		while (_i >= (_n < 0))                            \
			_s[_i--] = '0';                               \
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

#define DO_POSITIONAL(_f, _s, _specs, _ap)                                                \
	do                                                                                    \
	{                                                                                     \
		if (*_f == 'l')                                                                   \
		{                                                                                 \
			int _is_long = 0;                                                             \
			_f++;                                                                         \
			if (*_f == 'l')                                                               \
			{                                                                             \
				_f++;                                                                     \
				_is_long = 1;                                                             \
			}                                                                             \
			if (*_f == 'u')                                                               \
			{                                                                             \
				if (_is_long)                                                             \
					_s = _ft_printf_create_ull(va_arg(_ap, unsigned long long), &_specs); \
				else                                                                      \
					_s = _ft_printf_create_ul(va_arg(_ap, unsigned long), &_specs);       \
			}                                                                             \
			else if (*_f == 'd' || *_f == 'i')                                            \
			{                                                                             \
				if (_is_long)                                                             \
					_s = _ft_printf_create_ll(va_arg(_ap, long long), &_specs);           \
				else                                                                      \
					_s = _ft_printf_create_l(va_arg(_ap, long), &_specs);                 \
			}                                                                             \
		}                                                                                 \
		else if (*_f == '%')                                                              \
			_s = _ft_printf_create_c('%', &_specs);                                       \
		else if (*_f == 'c')                                                              \
			_s = _ft_printf_create_c(va_arg(_ap, int), &_specs);                          \
		else if (*_f == 's')                                                              \
			_s = _ft_printf_create_s(va_arg(_ap, char *), &_specs);                       \
		else if (*_f == 'p')                                                              \
			_s = _ft_printf_create_p(va_arg(_ap, size_t), &_specs);                       \
		else if (*_f == 'd' || *_f == 'i')                                                \
			_s = _ft_printf_create_di(va_arg(_ap, int), &_specs);                         \
		else if (*_f == 'u')                                                              \
			_s = _ft_printf_create_u(va_arg(_ap, unsigned int), &_specs);                 \
		else if (*_f == 'x' || *_f == 'X')                                                \
			_s = _ft_printf_create_xX(*_f, va_arg(_ap, int), &_specs);                    \
		if (!_s)                                                                          \
			return (-1);                                                                  \
	} while (0)

#endif // _CONVERSIONS_H
