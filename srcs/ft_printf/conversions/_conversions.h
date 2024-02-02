/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _conversions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:51:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 20:08:20 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONVERSIONS_H
# define _CONVERSIONS_H

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

__extern_always_inline size_t	_add_padding(int width, char c, int arg_length, int fd)
{
	int	done, padding;

	padding = width - arg_length;
	done = 0;
	if (width > 0)
		while (padding-- > 0)
			done += _ft_printf_out_c_internal(c, fd);
	return (done);
}

# define GET_NUMBER_LENGTH(_len_ptr, _type, _nb, _base) \
{ \
	do \
	{ \
		(*(_len_ptr)) = 0; \
		_type _tmp = _nb; \
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
	} while (0); \
}

#endif // _CONVERSIONS_H
