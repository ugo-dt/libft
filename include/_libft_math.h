/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:23:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/05 19:13:01 by ugdaniel         ###   ########.fr       */
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

# ifndef max
#  define max(a, b) ({\
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
     _a > _b ? _a : _b; })
# endif
# ifndef min
#  define min(a, b) ({\
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a < _b ? _a : _b; })
# endif
# ifndef clamp
#  define clamp(x, mn, mx) ({\
    typeof(x) _x = (x); \
    typeof(mn) _mn = (mn); \
    typeof(mx) _mx = (mx); \
    max(_mn, min(_mx, _x)); })
# endif

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
