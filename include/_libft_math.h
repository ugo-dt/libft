/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:23:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/06/15 16:27:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_MATH_H
# define _LIBFT_MATH_H

# include <stdint.h>
# include <stdlib.h>

# ifdef __cplusplus
extern "C" {
# endif

# ifdef __GNUC__
#  ifndef max
#   define max(a, b) ({\
     __typeof__(a) _a = (a); \
     __typeof__(b) _b = (b); \
      _a > _b ? _a : _b; })
#  endif
#  ifndef min
#   define min(a, b) ({\
     __typeof__(a) _a = (a); \
     __typeof__(b) _b = (b); \
     _a < _b ? _a : _b; })
#  endif
#  ifndef clamp
#   define clamp(x, mn, mx) ({\
    __typeof__(x) _x = (x); \
    __typeof__(mn) _mn = (mn); \
    __typeof__(mx) _mx = (mx); \
    max(_mn, min(_mx, _x)); })
#  endif
#else
# define _DECL_MIN_MAX_TYPE(T, ...) \
	static inline T _libft__min_##__VA_ARGS__(const T a, const T b) { return ((a) < (b)) ? (a) : (b); } \
	static inline T _libft__max_##__VA_ARGS__(const T a, const T b) { return ((a) > (b)) ? (a) : (b); }
_DECL_MIN_MAX_TYPE(signed char, c) _DECL_MIN_MAX_TYPE(unsigned char, uc)
_DECL_MIN_MAX_TYPE(signed short, s) _DECL_MIN_MAX_TYPE(unsigned short, us)
_DECL_MIN_MAX_TYPE(signed int, i) _DECL_MIN_MAX_TYPE(unsigned int, ui)
_DECL_MIN_MAX_TYPE(signed long, l) _DECL_MIN_MAX_TYPE(unsigned long, ul)
_DECL_MIN_MAX_TYPE(signed long long, ll) _DECL_MIN_MAX_TYPE(unsigned long long, ull)
_DECL_MIN_MAX_TYPE(float, f) _DECL_MIN_MAX_TYPE(double, d) _DECL_MIN_MAX_TYPE(long double, ld)
# define _libft__min_max_type_generic(a, b, _f) _Generic((b),	\
	signed char: _f##c,			unsigned char: _f##uc,			\
	signed short: _f##s,		unsigned short: _f##us,			\
	signed int: _f##i,			unsigned int: _f##ui,			\
	signed long: _f##l,			unsigned long: _f##ul,			\
	signed long long: _f##ll,	unsigned long long: _f##ull,	\
	float: _f##f,												\
	double: _f##d,												\
	long double: _f##ld											\
)((a), (b))
# define min(a, b) _libft__min_max_type_generic(a, b, _libft__min_)
# define max(a, b) _libft__min_max_type_generic(a, b, _libft__max_)
# endif // __GNUC__

/** The ft_abs() function computes the absolute value of the integer i.
 *
 * @return The absolute value.
 */
int			ft_abs(int i);

/** The ft_labs() function computes the absolute value of a long number x.
 *
 * @return The absolute value.
 */
long		ft_labs(long i);
long long   ft_llabs(long long x);

/** The fabs() functions compute the absolute value of a floating-point
 * number x.
 * @return The absolute value.
 */
double		ft_fabs(double x);
float		ft_fabsf(float x);
long double	ft_fabsl(long double x);

# ifdef __cplusplus
}
# endif

#endif // _LIBFT_MATH_H
