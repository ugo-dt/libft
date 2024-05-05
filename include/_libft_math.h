/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:23:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/05 11:08:11 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_MATH_H
# define _LIBFT_MATH_H

# include <stdlib.h>

# ifndef INT_MAX
#  define INT_MAX	2147483647
# endif
# ifndef INT_MIN
#  define INT_MIN	-2147483648
# endif

# ifdef __GNUC__
#  if __has_warning("-Wgnu-statement-expression-from-macro-expansion")
#   pragma GCC diagnostic ignored	"-Wgnu-statement-expression-from-macro-expansion"
#  endif
#  if __has_warning("-Wgnu-statement-expression")
#   pragma GCC diagnostic ignored	"-Wgnu-statement-expression"
#  endif
#  if __has_warning("-Wlanguage-extension-token")
#   pragma GCC diagnostic ignored	"-Wlanguage-extension-token"
#  endif
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
#  define min(a, b) (((a) < (b)) ? (a) : (b))
#  define max(a, b) (((a) > (b)) ? (a) : (b))
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
