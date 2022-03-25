/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:24:32 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/25 11:40:47 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_MATH_H
# define _FT_MATH_H	1

# if !defined _LIBFT_HEADER
#  error "Do not include "_ft_char.h" directly. Use "libft.h" instead."
# endif

/** The ft_abs() function computes the absolute value of the integer i.
 *
 * @return The absolute value.
 */
int	ft_abs(int i);

// TODO
/* The fabs() functions compute the absolute value of a floating-point
 * number x.
 * @return The absolute value.
 */
int	ft_fabs(double x);
int	ft_fabsl(long double x);
int	ft_fabsf(float x);

// TODO
/** The ft_labs() functions compute the absolute value of a long number x.
 *
 * @return The absolute value.
 */
int	ft_labs(long i);

#endif /* !defined _FT_MATH_H */
