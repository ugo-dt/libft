/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:29:51 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/26 13:09:14 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#if !defined ASCII_0
# define ASCII_0	48
#endif 

ssize_t	ft_putchar_len(char c, int fd);

ssize_t	ft_puthex_len(char x, unsigned int nb, int fd)
{
	ssize_t	done;
	int		caps;

	if (x == 'X')
		caps = 55;
	else
		caps = 87;
	done = 0;
	if (nb < 10)
		done += ft_putchar_len(nb + ASCII_0, fd);
	else if (nb < 16)
		done += ft_putchar_len(nb + caps, fd);
	else
	{
		done += ft_puthex_len(x, nb / 16, fd);
		done += ft_puthex_len(x, nb % 16, fd);
	}
	return (done);
}
