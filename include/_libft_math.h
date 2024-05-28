/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:23:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/08 16:58:13 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_MATH_H
# define _LIBFT_MATH_H

# include <stdint.h>
# include <stdlib.h>

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
# else
# define _DECL_MIN(T, ...)                                       \
	static inline T _ft__min##__VA_ARGS__(const T a, const T b) \
		{ return ((a) < (b)) ? (a) : (b); }
_DECL_MIN(int, i) _DECL_MIN(float, f) _DECL_MIN(double, d) _DECL_MIN(long, l) _DECL_MIN(long long, ll)
# define min(a, b) _Generic((b), \
	default:   _ft__mini,       \
	float:     _ft__minf,       \
	double:    _ft__mind,       \
	long:      _ft__minl,       \
	long long: _ft__minll)(a, b)

# define _DECL_MAX(T, ...)                                       \
	static inline T _ft__max##__VA_ARGS__(const T a, const T b) \
		{ return ((a) > (b)) ? (a) : (b); }
_DECL_MAX(int, i) _DECL_MAX(float, f) _DECL_MAX(double, d) _DECL_MAX(long, l) _DECL_MAX(long long, ll)
# define max(a, b) _Generic((b), \
	default:   _ft__maxi,       \
	float:     _ft__maxf,       \
	double:    _ft__maxd,       \
	long:      _ft__maxl,       \
	long long: _ft__maxll)(a, b)
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

#endif // _LIBFT_MATH_H
