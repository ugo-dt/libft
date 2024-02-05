/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _conversions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:51:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 19:52:41 by ugdaniel         ###   ########.fr       */
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
int		_ft_printf_out_c(char c, int fd, struct _specs *specs);
int		_ft_printf_out_s(const char *s, int fd, struct _specs *specs);
int		_ft_printf_out_p(size_t addr, int fd, struct _specs *specs);
int		_ft_printf_out_di(int nb, int fd, struct _specs *specs);
int		_ft_printf_out_u(unsigned int nb, int fd, struct _specs *specs);
void	_ft_printf_make_hex_string(char *s, char x, unsigned int nb, int alt, int length);
int		_ft_printf_out_xX(char x, unsigned int nb, int fd, struct _specs *specs);
int		_ft_printf_out_l(long nb, int fd, struct _specs *specs);
int		_ft_printf_out_ll(long long nb, int fd, struct _specs *specs);
int		_ft_printf_out_ul(unsigned long nb, int fd, struct _specs *specs);
int		_ft_printf_out_ull(unsigned long long nb, int fd, struct _specs *specs);

__extern_always_inline const unsigned char	*_ft_find_spec(const unsigned char *format)
{
	const unsigned char	*c = (const unsigned char *)ft_strchr((const char *)format, '%');
	if (!c)
		return format + ft_strlen((const char *)format);
	return (c);
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
