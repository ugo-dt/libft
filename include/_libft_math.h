/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _math.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:23:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/02/22 12:33:03 by ugdaniel         ###   ########.fr       */
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

/** The ft_abs() function computes the absolute value of the integer i.
 *
 * @return The absolute value.
 */
int			ft_abs(int i);

/** The ft_labs() functions compute the absolute value of a long number x.
 *
 * @return The absolute value.
 */
int			ft_labs(long i);

/** The fabs() functions compute the absolute value of a floating-point
 * number x.
 * @return The absolute value.
 */
double		ft_fabs(double x);
long double	ft_fabsl(long double x);
int			ft_fabsf(float x);

#endif // _LIBFT_MATH_H
