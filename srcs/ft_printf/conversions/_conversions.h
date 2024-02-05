/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _conversions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:51:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/04 10:20:32 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONVERSIONS_H
# define _CONVERSIONS_H

# include <stdlib.h>

size_t	_ft_printf_out_c_internal(char c, int fd);
size_t	_ft_printf_out_c(char c, int fd, int flag_left, int width);
size_t	_ft_printf_out_s(const char *s, int fd, int flag_left, int width);
size_t	_ft_printf_out_p(size_t addr, int fd, int flag_left, int width);
size_t	_ft_printf_out_di(int nb, int fd, int flag_zero, int flag_left, int width);
size_t	_ft_printf_out_u(unsigned int nb, int fd, int flag_zero, int flag_left, int width);
size_t	_ft_printf_out_xX(char x, unsigned int nb, int fd, int flag_hash, int flag_zero, int flag_left, int width);
size_t	_ft_printf_out_l(long nb, int fd, int flag_zero, int flag_left, int width);
size_t	_ft_printf_out_ll(long long nb, int fd, int flag_zero, int flag_left, int width);
size_t	_ft_printf_out_ul(unsigned long nb, int fd, int flag_zero, int flag_left, int width);
size_t	_ft_printf_out_ull(unsigned long long nb, int fd, int flag_zero, int flag_left, int width);

__extern_always_inline const unsigned char	*_ft_find_spec(const unsigned char *format)
{
	const unsigned char	*c = (const unsigned char *)ft_strchr((const char *)format, '%');
	if (!c)
		return format + ft_strlen((const char *)format);
	return (c);
}

__extern_always_inline char	*_append_c(char *s, int c, size_t n)
{
	while (n-- > 0)
		*s++ = c;
	return (s);
}

__extern_always_inline char	*_append_s(char *s, char *str, size_t n)
{
	while (n-- > 0)
		*s++ = *str++;
	return (s);
}

__extern_always_inline size_t	_add_padding_impl(int width, char c, int arg_length, int fd)
{
	size_t	done, padding;

	padding = width - arg_length;
	done = 0;
	while (padding-- > 0)
		done += _ft_printf_out_c_internal(c, fd);
	return (done);
}

# define _ADD_PADDING(_flag_zero, _output) \
	do \
	{ \
		if (width < (int)len) \
			width = (int)len; \
		if (!flag_left) \
			done += _add_padding_impl(width, _flag_zero ? '0' : ' ', len, fd); \
		_output \
		if (flag_left) \
			done += _add_padding_impl(width, ' ', done, fd); \
	} while (0)

# define _ADD_PADDING_SPACES(_output) _ADD_PADDING(0, _output)

# define GET_NUMBER_LENGTH(_len_ptr, _nb, _base) \
	do \
	{ \
		(*(_len_ptr)) = 0; \
		typeof(_nb) _tmp = _nb; \
		if (_tmp < 0) \
		{ \
			(*(_len_ptr))++; \
			_tmp = -_tmp; \
		} \
		_tmp = _nb; \
		(*(_len_ptr)) = 1; \
		while (_tmp > _base) \
		{ \
			_tmp /= _base; \
			(*(_len_ptr))++; \
		} \
	} while (0)

# define CREATE_STRING(_s, _full_length, _padding, _flag_left, _flag_zero, _output) \
	do \
	{ \
		_s = malloc(sizeof(char) * _full_length); \
		if (!_s) \
			return (-1); \
		char *_cur = _s; \
		if (!_flag_left) \
			_cur = _append_c(_cur, _flag_zero ? '0' : ' ', _padding); \
		_output; \
		if (_flag_left) \
			_cur = _append_c(_cur, ' ', _padding); \
	} while (0)

# define APPEND_CHAR(_c, _length) (_cur = _append_c(_cur, _c, _length))
# define APPEND_STRING(_str, _length) (_cur = _append_s(_cur, _str, _length))

#endif // _CONVERSIONS_H
