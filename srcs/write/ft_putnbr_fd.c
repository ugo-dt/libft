/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:39:27 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/29 12:28:24 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_write.h"

#ifndef __INT_MIN
# define __INT_MIN__	-2147483648
#endif

void	ft_putnbr_fd(int n, int __fd)
{
	if (n == __INT_MIN__)
	{
		ft_putnbr_fd(__INT_MIN__, __fd);
		ft_putchar_fd('8', __fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', __fd);
		ft_putnbr_fd(-n, __fd);
	}
	else if (n < 10)
		ft_putchar_fd(n + 48, __fd);
	else
	{
		ft_putnbr_fd(n / 10, __fd);
		ft_putnbr_fd(n % 10, __fd);
	}
}
